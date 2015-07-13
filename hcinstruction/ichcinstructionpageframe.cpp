#include "ichcinstructionpageframe.h"
#include "ui_ichcinstructionpageframe.h"

#include <QDir>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileInfoList>

#include "icmold.h"
#include "actionsettingframe.h"
#include "ichcfixturepage.h"
#include "ichcinjectionpage.h"
#include "ichcconditionpage.h"
#include "icflagseditor.h"
#include "icpneumaticactionpage.h"
#include "icwaitconditioneditor.h"
#include "icperipherypage.h"
#include "iccutpage.h"
#include "icprogramselector.h"
#include "icstackeditor.h"
#include "icparameterssave.h"
#include "icinstructparam.h"
#include "iccommandprocessor.h"
#include "icvirtualkey.h"
#include "icvirtualhost.h"
#include "moldinformation.h"
#include "icactioncommand.h"
#include "icmacrosubroutine.h"
#include "icprogramheadframe.h"
#include "icinstructioneditorbase.h"
#include "mainframe.h"
#include "ickeyboard.h"
#include "icactioncommand.h"
#include "icprogramguidepage.h"
#include "ichcotherpage.h"
#include "iccommenteditor.h"

#include <QDebug>
#include <QMessageBox>

//struct MoldItem
//{
//    int stepNum;
//    int
//};

ICHCInstructionPageFrame::ICHCInstructionPageFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ICHCInstructionPageFrame),
    injectionPage_(NULL),
    fixturePage_(NULL),
    conditionPage_(NULL),
    flagsPage_(NULL),
    pneumaticPage_(NULL),
    waitConditionPage_(NULL),
    peripheryPage_(NULL),
    cutPage_(NULL),
    programPage_(NULL),
    stackPage_(NULL),
    guidePage_(NULL),
    otherPage_(NULL),
    commentPage_(NULL),
    recordPath_("./records/"),
    currentAction_(None),
    currentEdit_(0),
    isProgramChanged_(false),
    isModifyProgram_(false)
{
    ui->setupUi(this);
//    ui->otherButton->hide();

    InitInterface();
    InitSignal();
//    ui->moldContentListWidget->setBackgroundRole(QColor("gray"));

//    LoadAllRecordFileInfo();

    InitParameter();

//    ui->conditionsToolButton->hide();
}

ICHCInstructionPageFrame::~ICHCInstructionPageFrame()
{
    delete modifyDialog_;
    delete ui;
}

void ICHCInstructionPageFrame::showEvent(QShowEvent *e)
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    if(host->AxisDefine(ICVirtualHost::ICAxis_AxisA) == ICVirtualHost::ICAxisDefine_None)
    {
        ui->aMinusBtn->hide();
        ui->aPlusBtn->hide();
    }
    else
    {
        ui->aMinusBtn->show();
        ui->aPlusBtn->show();
    }
    if(ICParametersSave::Instance()->IsExtentFunctionUsed())
    {
        ui->flagsButton->show();
        ui->conditionsToolButton->show();
    }
    else
    {
        ui->flagsButton->hide();
        ui->conditionsToolButton->hide();
    }
    QFrame::showEvent(e);
//    connect(ICVirtualHost::GlobalVirtualHost(),
//            SIGNAL(StepChanged(int)),
//            this,
//            SLOT(SelectCurrentStep(int)));
//    connect(ICVirtualHost::GlobalVirtualHost(),
//            SIGNAL(NeedToGetTeach()),
//            this,
//            SLOT(GetTeachContent()));
//    ICCommandProcessor::Instance()->ExecuteHCCommand(IC::CMD_TurnTeach,
//                                                     0,
//                                                     ICMold::CurrentMold()->SyncAct() + ICMacroSubroutine::Instance()->SyncAct(),
//                                                     ICMold::CurrentMold()->SyncSum() + ICMacroSubroutine::Instance()->SyncSum());
    UpdateHostParam();
//    if(!icMainFrame->IsOrigined())
//    {
//        QMessageBox::warning(this, tr("Warning"), tr("Need to origin!"));
//    }
}

void ICHCInstructionPageFrame::hideEvent(QHideEvent *e)
{
    qDebug("instruct hide");
    modifyDialog_->hide();
    QFrame::hideEvent(e);
//    disconnect(ICVirtualHost::GlobalVirtualHost(),
//               SIGNAL(StepChanged(int)),
//               this,
//               SLOT(SelectCurrentStep(int)));
//    disconnect(ICVirtualHost::GlobalVirtualHost(),
//               SIGNAL(NeedToGetTeach()),
//               this,
//               SLOT(GetTeachContent()));
//    ICMold::CurrentMold()->SetMoldContent(ICMold::UIItemToMoldItem(programList_));
//    ICMold::CurrentMold()->SaveMoldFile();
    if(isModifyProgram_ || isProgramChanged_)
    {
        SaveCurrentEdit();
        ICVirtualHost::GlobalVirtualHost()->ReConfigure();
        isProgramChanged_ = false;
        isModifyProgram_ = false;
    }
    if(ICKeyboard::Instace()->CurrentSwitchStatus() == ICKeyboard::KS_ManualStatu)
    {
        ICCommandProcessor::Instance()->ExecuteHCCommand(IC::CMD_TurnManual, 0);
    }

 //   ICInstructParam::Instance()->UpdateHostParam();

}

void ICHCInstructionPageFrame::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        ICInstructParam::Instance()->UpdateTranslate();
        break;
    default:
        break;
    }
}


void ICHCInstructionPageFrame::OptionButtonClicked()
{
    QAbstractButton * optionButton = qobject_cast<QAbstractButton *>(sender());

    if(injectionPage_ == NULL && optionButton == ui->injectionButton)
    {
        injectionPage_ = new ICHCInjectionPage;
        optionButtonToPage_.insert(ui->injectionButton, injectionPage_);
        ui->settingStackedWidget->addWidget(injectionPage_);

    }
    else if(fixturePage_ == NULL && optionButton == ui->fixtureButton)
    {
        fixturePage_ = new ICHCFixturePage;
        optionButtonToPage_.insert(ui->fixtureButton, fixturePage_);
        ui->settingStackedWidget->addWidget(fixturePage_);
    }
    else if(conditionPage_ == NULL && optionButton == ui->conditionsToolButton)
    {
        conditionPage_ = new ICHCConditionPage;
        optionButtonToPage_.insert(ui->conditionsToolButton, conditionPage_);
        ui->settingStackedWidget->addWidget(conditionPage_);
    }
    else if(flagsPage_ == NULL && optionButton == ui->flagsButton)
    {
        flagsPage_ = new ICFlagsEditor();
        optionButtonToPage_.insert(ui->flagsButton, flagsPage_);
        ui->settingStackedWidget->addWidget(flagsPage_);
    }
    else if(pneumaticPage_ == NULL && optionButton == ui->pneumaticButton)
    {
        pneumaticPage_ = new ICPneumaticActionPage();
        optionButtonToPage_.insert(ui->pneumaticButton, pneumaticPage_);
        ui->settingStackedWidget->addWidget(pneumaticPage_);
    }
    else if(waitConditionPage_ == NULL && optionButton == ui->waitToolButton)
    {
        waitConditionPage_ = new ICWaitConditionEditor();
        optionButtonToPage_.insert(ui->waitToolButton, waitConditionPage_);
        ui->settingStackedWidget->addWidget(waitConditionPage_);
    }
    else if(peripheryPage_ == NULL && optionButton == ui->peripheryButton)
    {
        peripheryPage_ = new ICPeripheryPage();
        optionButtonToPage_.insert(ui->peripheryButton, peripheryPage_);
        ui->settingStackedWidget->addWidget(peripheryPage_);
    }
    else if(cutPage_ == NULL && optionButton == ui->cutButton)
    {
        cutPage_ = new ICCutPage();
        optionButtonToPage_.insert(ui->cutButton, cutPage_);
        ui->settingStackedWidget->addWidget(cutPage_);
    }
    else if(programPage_ == NULL && optionButton == ui->programButton)
    {
        programPage_ = new ICProgramSelector();
        optionButtonToPage_.insert(ui->programButton, programPage_);
        ui->settingStackedWidget->addWidget(programPage_);
        connect(programPage_,
                SIGNAL(ProgramChanged(int, QString)),
                this,
                SLOT(OnProgramChanged(int, QString)));
    }
    else if(stackPage_ == NULL && optionButton == ui->stackButton)
    {
        stackPage_ = new ICStackEditor();
        optionButtonToPage_.insert(ui->stackButton, stackPage_);
        ui->settingStackedWidget->addWidget(stackPage_);
    }
    else if(guidePage_ == NULL && optionButton == ui->guideButton)
    {
        guidePage_ = new ICProgramGuidePage();
        optionButtonToPage_.insert(ui->guideButton, guidePage_);
        ui->settingStackedWidget->addWidget(guidePage_);
        connect(guidePage_,
                SIGNAL(GuideFinished()),
                SLOT(OnGuideFinished()));
    }
    else if(otherPage_ == NULL && optionButton == ui->otherButton)
    {
        otherPage_ = new ICHCOtherPage();
        optionButtonToPage_.insert(ui->otherButton, otherPage_);
        ui->settingStackedWidget->addWidget(otherPage_);
    }
    else if(commentPage_ == NULL && optionButton == ui->commentButton)
    {
        commentPage_ = new ICCommentEditor();
        optionButtonToPage_.insert(ui->commentButton, commentPage_);
        ui->settingStackedWidget->addWidget(commentPage_);
    }
    if(optionButton == ui->conditionsToolButton)
    {

        conditionPage_->ResetFlagSel(Flags());
    }
    ui->settingStackedWidget->setCurrentWidget(optionButtonToPage_.value(optionButton));
}

void ICHCInstructionPageFrame::InitInterface()
{
    //    ui->settingFrame->setLayout(ui->settingStackedWidget);

    actionPage_ = new ActionSettingFrame(ui->actionSelectPage);
    optionButtonToPage_.insert(ui->lineButton, actionPage_);
    ui->settingStackedWidget->addWidget(actionPage_);
    modifyDialog_ = new ICInstructModifyDialog(this);
    //    injectionPage_ = new ICHCInjectionPage;
    //    optionButtonToPage_[ui->injectionButton] = injectionPage_;
    //    ui->settingStackedWidget->addWidget(injectionPage_);

    //    fixturePage_ = new ICHCFixturePage;
    //    optionButtonToPage_[ui->fixtureButton] = fixturePage_;
    //    ui->settingStackedWidget->addWidget(fixturePage_);

    //    conditionPage_ = new ICHCConditionPage;
    //    optionButtonToPage_[ui->conditionsToolButton] = conditionPage_;
    //    ui->settingStackedWidget->addWidget(conditionPage_);

//    ui->settingStackedWidget->setCurrentWidget(actionPage_);
}

void ICHCInstructionPageFrame::InitSignal()
{
    connect(ui->lineButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->injectionButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->fixtureButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->conditionsToolButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));

    connect(ui->flagsButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->pneumaticButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->waitToolButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->peripheryButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->cutButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->programButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->stackButton,
            SIGNAL(clicked()),
            this,
            SLOT(OptionButtonClicked()));
    connect(ui->aMinusBtn,
            SIGNAL(released()),
            SLOT(OnActionButtonReleased()));
    connect(ui->aPlusBtn,
            SIGNAL(released()),
            SLOT(OnActionButtonReleased()));
    connect(ui->guideButton,
            SIGNAL(clicked()),
            SLOT(OptionButtonClicked()));
    connect(ui->otherButton,
            SIGNAL(clicked()),
            SLOT(OptionButtonClicked()));
    connect(ui->commentButton,
            SIGNAL(clicked()),
            SLOT(OptionButtonClicked()));
}

void ICHCInstructionPageFrame::InitParameter()
{
    QString recordName = ICParametersSave::Instance()->MoldName("TEST.act");

//    ui->programSelectedComboBox->setCurrentIndex(ui->programSelectedComboBox->findText(recordName));

//    ICInstructParam::Instance()->UpdateHostParam();
    UpdateHostParam();
    //    LoadMoldFile(recordName);
}

void ICHCInstructionPageFrame::UpdateHostParam()
{
    qDebug("update");
    qDebug()<<"Update"<<currentEdit_;
    qDebug()<<"UpdateMold size"<<ICMold::CurrentMold()->MoldContent().size();
    if(currentEdit_ == 0)
    {
        programList_ = ICMold::CurrentMold()->ToUIItems();
    }
    else
    {
        programList_ = ICMold::MoldItemToUIItem(ICMacroSubroutine::Instance()->SubRoutine(currentEdit_ - 1));
    }
    qDebug("after update");
    UpdateUIProgramList_();
}

void ICHCInstructionPageFrame::UpdateUIProgramList_()
{
    ui->moldContentListWidget->clear();
    qDebug("after clear");

    ui->moldContentListWidget->addItems(ICMold::UIItemsToStringList(programList_));
    ICGroupMoldUIItem groupItem;
    int topItemRowCount;
    int index = 0;
    QColor color;
    ICMoldItem* tmp = NULL;
    for(int i = 0; i != programList_.size(); ++i)
    {
        (i % 2 == 0 ? color.setRgb(255,255,154): color.setRgb(154,255,255));
//        (i % 2 == 0 ? color.setRgb(191,255,191): color.setRgb(222,255,222));
//        (i % 2 == 0 ? color.setRgb(255,255,154): color.setRgb(191,255,191));
        groupItem = programList_.at(i);
        topItemRowCount = groupItem.ItemCount();
        for(int j = 0; j != topItemRowCount; ++j)
        {
            tmp = groupItem.MoldItemAt(j);
            if(tmp != NULL)
            {
                if(tmp->Num() == 0)
                {
                    ui->moldContentListWidget->item(j + index)->setBackgroundColor(QColor(239, 235, 231));
//                    ui->moldContentListWidget->item(j + index)->setForeground(QColor("white"));
                }
                else if(tmp->Action() == ICInstructParam::ACT_WaitMoldOpened)
                {
                    ui->moldContentListWidget->item(j + index)->setBackgroundColor("red");
                }
                else
                {
                    ui->moldContentListWidget->item(j + index)->setBackgroundColor(color);
                }
            }
        }
        index += topItemRowCount;
    }
    qDebug("updatge end");
}

void ICHCInstructionPageFrame::on_insertToolButton_clicked()
{
    if(guidePage_)  //限制在教导页面点击插入的时候出现错误
    {
        if(!guidePage_->isHidden())
        {
            return;  //教导页面点插入无任何动作
        }
    }
    if(MoldInformation::Instance()->IsStandProgram(ICParametersSave::Instance()->MoldName("")))
    {
        QMessageBox::warning(this, tr("warning"),
                             tr("Stand program can not be insert action"));
        return;
   }
    ICInstructionEditorBase* editor = qobject_cast<ICInstructionEditorBase*>(ui->settingStackedWidget->currentWidget());
    ICFlagsEditor *flagsEditor = qobject_cast<ICFlagsEditor*> (editor);
    ActionSettingFrame *servoEditor = qobject_cast<ActionSettingFrame*>(editor);
    ICCommentEditor *commentEdit = qobject_cast<ICCommentEditor*>(editor);
    if(editor == NULL)
    {
        return;
    }
    int index = ui->moldContentListWidget->currentRow();
    int gIndex;
    int tIndex;
    int sIndex;
    if(index < 0)
    {
        return;
    }
    FindIndex_(index, gIndex, tIndex, sIndex);
    QString currentmoldname  = ICParametersSave::Instance()->MoldName("");
    /******currentEdit_标记为0表示为主程序（主程序时不能删除待机点）*****/
    if(programList_.at(gIndex).StepNum() == 0 && currentEdit_ == 0 && currentmoldname.left(4) != "szhc")
    {
        QMessageBox::warning(this,
                             tr("Warning"),
                             tr("Can not add standby position program"));
        return;
    }
    bool isParallel = false;
    bool isServo = false;
    bool isComment = false;
    if(flagsEditor != NULL)
    {
        isParallel = true;
    }
    if(servoEditor != NULL)
    {
        isServo = true;
    }
    if(commentEdit != NULL)
    {
        isComment = true;
    }
    QList<ICMoldItem> items = editor->CreateCommand();
    if(items.isEmpty() && !isParallel)
    {
        return;
    }
    if(isComment)
    {
        items[0].SetFlag(ValidFlag());
    }
    if(sIndex == -1)
    {
        if(tIndex == 0) //insert GroupItem
        {
            QList<ICGroupMoldUIItem> insertedGroupItems;
            if(isParallel)
            {
                ICGroupMoldUIItem groupItem;
                ICTopMoldUIItem topItem = flagsEditor->CreateTopUIItem();
                groupItem.AddToMoldUIItem(topItem);
                groupItem.SetStepNum(gIndex);
                insertedGroupItems.append(groupItem);
            }
            else if(isServo)
            {
                ICTopMoldUIItem topItem;
                ICGroupMoldUIItem groupItem;
                for(int i = 0; i != items.size(); ++i)
                {
                    topItem.SetBaseItem(items.at(i));
                    groupItem.AddToMoldUIItem(topItem);
                }
                groupItem.SetStepNum(gIndex);
                insertedGroupItems.append(groupItem);
            }
//            else if(isComment)
//            {
//                ICTopMoldUIItem topItem;
//                topItem.SetBaseItem(items.at(0));
//                if(programList_[gIndex].MoldItemAt(0)->Action() == ICMold::ACTEND &&
//                        gIndex != 0)
//                {
//                    topItem.SetStepNum(gIndex - 1);
//                    programList_[gIndex - 1].AddToMoldUIItem(topItem);
//                }
//                else if(programList_[gIndex].MoldItemAt(0)->Action() == ICMold::ACTEND &&
//                        gIndex == 0)
//                {
//                    return;
//                }
//                else
//                    programList_[gIndex].PrependTopMoldUIItem(topItem);
//            }
            else
            {
                ICTopMoldUIItem topItem;
                for(int i = 0; i != items.size(); ++i)
                {
                    topItem.SetBaseItem(items.at(i));
                    ICGroupMoldUIItem groupItem;
                    groupItem.AddToMoldUIItem(topItem);
                    groupItem.SetStepNum(gIndex + i);
                    insertedGroupItems.append(groupItem);
                }
            }
            const int addedCount = insertedGroupItems.size();
            for(int i = gIndex; i != programList_.size(); ++i)
            {
                programList_[i].SetStepNum(i + addedCount);
            }
            for(int i = 0; i != insertedGroupItems.size(); ++i)
            {
                programList_.insert(gIndex++, insertedGroupItems.at(i));
            }
        }
        else  //insert TopItem
        {
            QList<ICTopMoldUIItem> insertedTopItems;
            ICTopMoldUIItem topItem;
            const int stepNum = programList_.at(gIndex).StepNum();
            if(isParallel)
            {
                topItem = flagsEditor->CreateTopUIItem();
                topItem.SetStepNum(stepNum);
                insertedTopItems.append(topItem);
            }
            else
            {
                for(int i = 0; i != items.size(); ++i)
                {
                    topItem.SetBaseItem(items.at(i));
                    topItem.SetStepNum(stepNum);
                    insertedTopItems.append(topItem);
                }
            }
            for(int i = 0; i != insertedTopItems.size(); ++i)
            {
                programList_[gIndex].InsertTopItem(tIndex++, insertedTopItems.at(i));
            }
        }
    }
    else //insert SubItem
    {
        if(isParallel)
        {
            return;
        }
        if(isComment)
        {
            return;
        }
        QList<ICSubMoldUIItem> insertedSubItems;
        ICSubMoldUIItem item;
        const int stepNum = programList_.at(gIndex).StepNum();
        const int subNum = programList_.at(gIndex).at(tIndex).at(sIndex).SubNum();
        bool isSyncItem;
        if(sIndex == 0)
        {
            isSyncItem = false;
        }
        else
        {
            isSyncItem = programList_.at(gIndex).at(tIndex).at(sIndex).SubNum() ==
                    programList_.at(gIndex).at(tIndex).at(sIndex - 1).SubNum();
        }
        for(int i = 0; i != items.size(); ++i)
        {
            item.SetBaseItem(items.at(i));
            item.SetStepNum(stepNum);
            item.SetSyncItem(isSyncItem);
            isSyncItem ? item.SetSubNum(subNum):item.SetSubNum(subNum + i);
            insertedSubItems.append(item);
        }
        ICTopMoldUIItem* topItem = &programList_[gIndex].at(tIndex);
        for(int i = 0; i != insertedSubItems.size(); ++i)
        {
            topItem->InsertSubMoldUIItem(sIndex++, insertedSubItems.at(i));
        }
        if(!isSyncItem)
        {
            int addCount = insertedSubItems.size();
            for(int i = sIndex; i != topItem->SubItemCount(); ++i)
            {
                topItem->at(i).SetSubNum(topItem->at(i).SubNum() + addCount);
            }
        }

//        topItem->ReCalSubNum();
    }
    UpdateUIProgramList_();
    index += items.size();
    if(index >= ui->moldContentListWidget->count())
    {
        index = ui->moldContentListWidget->count() - 1;
    }
    ui->moldContentListWidget->setCurrentRow(index);
    isModifyProgram_ = true;
}

void ICHCInstructionPageFrame::on_modifyToolButton_clicked()
{
    QList<QListWidgetItem*> items = ui->moldContentListWidget->selectedItems();
    if(items.isEmpty())
    {
        return;
    }
    modifyDialog_->ResetFlagSel(Flags());
    const int selectedRow = ui->moldContentListWidget->row(items.at(0));
    int gIndex;
    int tIndex;
    int sIndex;
    FindIndex_(selectedRow, gIndex, tIndex, sIndex);
    if(sIndex < 0)
    {
        ICTopMoldUIItem * topItem = &programList_[gIndex].at(tIndex);
        ICMoldItem* item = topItem->BaseItem();
        bool isModify = modifyDialog_->ShowModifyItem(item);
        if(isModify)
        {
            ui->moldContentListWidget->item(selectedRow)->setText(topItem->ToStringList().at(0));
        }
    }
    else
    {
        ICSubMoldUIItem *subItem = &programList_[gIndex].at(tIndex).at(sIndex);
        bool isModify = modifyDialog_->ShowModifyItem(subItem->BaseItem());
        if(isModify)
        {
            ui->moldContentListWidget->item(selectedRow)->setText(subItem->ToString());
        }

    }
    isModifyProgram_ = true;
//    if(isModify)

}

void ICHCInstructionPageFrame::on_deleteToolButton_clicked()
{
    int currentRow = ui->moldContentListWidget->currentRow();
    if(currentRow == ui->moldContentListWidget->count() - 1)
    {
        return;
    }
    if(currentRow < 0)
    {
        return;
    }
    if(MoldInformation::Instance()->IsStandProgram(ICParametersSave::Instance()->MoldName("")))
    {
        QMessageBox::warning(this, tr("warning"),
                             tr("Stand program can not be delete action"));
        return;
   }
    int gIndex;
    int tIndex;
    int sIndex;
    FindIndex_(currentRow, gIndex, tIndex, sIndex);
    /************BUG181:子程序位置插入后不能删除******************/

    QString currentmoldname  = ICParametersSave::Instance()->MoldName("");
    if(programList_.at(gIndex).StepNum() == 0 && currentEdit_ == 0 && currentmoldname.left(4) != "szhc")
    {
        QMessageBox::warning(this,
                             tr("Warning"),
                             tr("Can not delete standby position program"));
        return;
    }
    if(sIndex == -1)
    {
        if(programList_[gIndex].TopItemCount() == 1) //delete Group Item
        {
            programList_.removeAt(gIndex);
            for(int i = gIndex; i != programList_.size(); ++i)
            {
                programList_[i].SetStepNum(i);
            }
        }
        else
        {
            programList_[gIndex].RemoveTopItem(tIndex);
            if(programList_[gIndex].RunableTopItemCount() == 0)
            {
                programList_[gIndex].SetStepNum(gIndex - 1);
                if(gIndex > 0 )
                {
                    for(int i = 0 ; i != programList_[gIndex].TopItemCount(); ++i)
                    {
                        ICTopMoldUIItem topItem;
                        topItem.SetBaseItem(*(programList_[gIndex].MoldItemAt(i)));
                        programList_[gIndex - 1].AddToMoldUIItem(topItem);
                    }
                }
                programList_.removeAt(gIndex);
                for(int i = gIndex; i != programList_.size(); ++i)
                {
                    programList_[i].SetStepNum(i);
                }
            }
        }
    }
    else
    {
        ICTopMoldUIItem* topItem = &programList_[gIndex].at(tIndex);
        bool isSyncItem = topItem->IsSyncSubItem(sIndex);
//        if(topItem->SubItemCount() == 1)
//        {
//            isSyncItem = false;
//        }
//        else if(sIndex == 0)
//        {
//            isSyncItem = topItem->at(sIndex + 1).SubNum() == topItem->at(sIndex).SubNum();
//        }
//        else if(sIndex == topItem->SubItemCount() - 1)
//        {
//            isSyncItem = topItem->at(sIndex - 1).SubNum() == topItem->at(sIndex).SubNum();
//        }
//        else
//        {
//            isSyncItem = (topItem->at(sIndex + 1).SubNum() == topItem->at(sIndex).SubNum()) ||
//                    topItem->at(sIndex - 1).SubNum() == topItem->at(sIndex).SubNum();
//        }
        topItem->RemoveSubItem(sIndex);
        if(topItem->ItemCount() == 1)
        {
            programList_[gIndex].RemoveTopItem(tIndex);
            programList_.removeAt(gIndex);
            for(int i = gIndex; i != programList_.size(); ++i)
            {
                programList_[i].SetStepNum(i);
            }
        }
        else
        {
            if(!isSyncItem)
            {
                for(int i = sIndex; i != topItem->SubItemCount(); ++i)
                {
                    topItem->at(i).SubNumMinus();
                }
            }
        }
    }
    UpdateUIProgramList_();

    if(currentRow >= ui->moldContentListWidget->count())
    {
        currentRow = ui->moldContentListWidget->count() - 1;
    }
    ui->moldContentListWidget->setCurrentRow(currentRow);
    isModifyProgram_ = true;
}

//void ICHCInstructionPageFrame::LoadFileInfoButtonClicked(const QString &moldName)
//{
//    if(ICParametersSave::Instance()->MoldName(QString()) != moldName)
//    {
//        on_programSelectedComboBox_activated(moldName);
//    }
//}

//void ICHCInstructionPageFrame::NewFileCreated(const QString & moldName)
//{
//    ui->programSelectedComboBox->addItem(moldName);
//}

//void ICHCInstructionPageFrame::DeleteFile(const QString & moldName)
//{
//    ui->programSelectedComboBox->removeItem(
//                ui->programSelectedComboBox->findText(moldName));
//}

void ICHCInstructionPageFrame::on_commandButton_clicked()
{
    ui->settingStackedWidget->setCurrentIndex(0);
}

void ICHCInstructionPageFrame::FindIndex_(int currentIndex, int& groupItemIndex, int &topItemIndex, int &subItemIndex)
{
    for(int i = 0; i != programList_.size(); ++i)
    {
        if(currentIndex < programList_.at(i).ItemCount())
        {
            groupItemIndex = i;
            for(int j = 0; j != programList_.at(i).TopItemCount(); ++j)
            {
                if(currentIndex < programList_.at(i).at(j).ItemCount())
                {
                    topItemIndex = j;
                    if(currentIndex == 0)
                    {
                        subItemIndex = -1;
                    }
                    else
                    {
                        subItemIndex = currentIndex - 1;
                    }
                    break;
                }
                else
                {
                    currentIndex -= programList_.at(i).at(j).ItemCount();
                }
            }
            break;
        }
        else
        {
            currentIndex -= programList_.at(i).ItemCount();
        }
    }
}

void ICHCInstructionPageFrame::on_upButton_clicked()
{
    int gIndex;
    int tIndex;
    int sIndex;
    const int currentRow = ui->moldContentListWidget->currentRow();
    if(currentRow < 0 || currentRow >= ui->moldContentListWidget->count() - 1)
    {
        return;
    }
    if(MoldInformation::Instance()->IsStandProgram(ICParametersSave::Instance()->MoldName("")))
    {
        QMessageBox::warning(this, tr("warning"),
                             tr("Stand program can not do Up action"));
        return;
   }
    FindIndex_(currentRow, gIndex, tIndex, sIndex);
    //子程序也可以分解和组合，所以无需判断
//    if(programList_.at(gIndex).StepNum() == 1)
//    {
//        QMessageBox::warning(this,
//                             tr("Warning"),
//                             tr("Can not group up to standby position program"));
//        return;
//    }
    if(sIndex == -1)
    {
        if(gIndex == 0)
        {
            return;
        }
        if(gIndex == programList_.size() - 1)
        {
            return;
        }
        ICGroupMoldUIItem *item = &programList_[gIndex];
//        if(item->MoldItemAt(0)->Action() == ICMold::ACTCOMMENT) return;
        int runableCount = 0;
        for(int i = 0; i != item->TopItemCount(); ++i)
        {
            if(item->MoldItemAt(i)->Action() != ICMold::ACTCOMMENT)
                ++runableCount;
        }
//        if(item->TopItemCount() == 1) //group up
//        {
//            item->SetStepNum(gIndex - 1);
//            programList_[gIndex - 1].AddToMoldUIItem(item->at(0));
//            programList_.removeAt(gIndex);
//            for(int i = gIndex; i != programList_.size(); ++i)
//            {
//                programList_[i].SetStepNum(i);
//            }
//        }
        if(runableCount < 2 || item->TopItemCount() == 1)
        {
            item->SetStepNum( gIndex - 1);
            for(int i = 0 ; i != item->TopItemCount(); ++i)
            {
                programList_[gIndex  -1].AddToMoldUIItem(item->at(i));
            }
            programList_.removeAt(gIndex);
            for(int i = gIndex; i != programList_.size(); ++i)
            {
                programList_[i].SetStepNum(i);
            }
        }
        else if(tIndex == 0)
        {
            programList_[gIndex - 1].AddToMoldUIItem(item->at(0));
            programList_[gIndex - 1].SetStepNum(gIndex - 1);
            programList_[gIndex].RemoveTopItem(tIndex);
        }
    }
    else
    {
        if(programList_[gIndex].at(tIndex).at(sIndex).SubNum() == 0)
        {
            return;
        }

        ICTopMoldUIItem *topItem = &programList_[gIndex].at(tIndex);
        ICSubMoldUIItem *subItem = &topItem->at(sIndex);
        int subNum = subItem->SubNum();
        if(subNum != topItem->at(sIndex - 1).SubNum())
        {
            bool isSync = topItem->IsSyncSubItem(sIndex);
            topItem->at(sIndex - 1).SetSyncItem(true);
            subItem->SubNumMinus();
            subItem->SetSyncItem(true);
            if(!isSync)
            {
                for(int i = sIndex + 1; i != topItem->SubItemCount(); ++i)
                {
                    topItem->at(i).SubNumMinus();
                }
            }
        }
    }
//    isEdit_ = true;
    UpdateUIProgramList_();
    isModifyProgram_ = true;
}

void ICHCInstructionPageFrame::on_downButton_clicked()
{
    int gIndex;
    int tIndex;
    int sIndex;
    const int currentRow = ui->moldContentListWidget->currentRow();
    if(currentRow < 0)
    {
        return;
    }
    if(MoldInformation::Instance()->IsStandProgram(ICParametersSave::Instance()->MoldName("")))
    {
        QMessageBox::warning(this, tr("warning"),
                             tr("Stand program can not do Down action"));
        return;
   }
    FindIndex_(currentRow, gIndex, tIndex, sIndex);
    //子程序也可以分解和组合，所以无需判断
//    if(programList_.at(gIndex).StepNum() == 0)
//    {
//        QMessageBox::warning(this,
//                             tr("Warning"),
//                             tr("Can not decompose standby position program"));
//        return;
//    }
    if(sIndex == -1)
    {
        if(gIndex == 0 && tIndex == 0)// if is the first TopItem, do nothing
        {
            return;
        }
        if(gIndex >= programList_.size() - 1) //if is the last two item, do nothing
        {
            return;
        }
        if(tIndex == 0)
        {
            return;
        }
        ICGroupMoldUIItem* groupItem = &programList_[gIndex];
//        if(groupItem->MoldItemAt(0)->Action() == ICMold::ACTCOMMENT) return;
        if(groupItem->ItemCount() == 1) //group item down
        {
            groupItem->AddOtherGroup(programList_.at(gIndex + 1));
            programList_.removeAt(gIndex + 1);
            for(int i = gIndex; i != programList_.size(); ++i)
            {
                programList_[i].SetStepNum(i);
            }
        }
        else //split group item
        {
            if(groupItem->MoldItemAt(tIndex)->Action() == ICMold::ACTCOMMENT) return;
            bool up = false;
            bool dw = false;
            int runableCount = 0;
            for(int i = 0; i != tIndex; ++i)
            {
                if(groupItem->MoldItemAt(i)->Action() != ICMold::ACTCOMMENT)
                    ++runableCount;
            }
            if(runableCount == 0) return;
            runableCount = 0;
            for(int i = tIndex; i != groupItem->ItemCount(); ++i)
            {
                if(groupItem->MoldItemAt(i)->Action() != ICMold::ACTCOMMENT)
                    ++runableCount;
            }
            if(runableCount == 0 ) return;
//            if(groupItem->MoldItemAt(tIndex - 1)->Action() == ICMold::ACTCOMMENT &&
//                    groupItem->RunableTopItemCount() < 2) return;
//            if(groupItem->MoldItemAt(groupItem->ItemCount() - 1)->Action() == ICMold::ACTCOMMENT) return;
            QList<ICGroupMoldUIItem> gItems = programList_.at(gIndex).SpliteToTwoGroup(tIndex);
            gItems[0].SetStepNum(gIndex);
            gItems[1].SetStepNum(gIndex + 1);
            programList_.removeAt(gIndex);
            programList_.insert(gIndex++, gItems.at(0));
            programList_.insert(gIndex++, gItems.at(1));
            for(int i = gIndex; i != programList_.size(); ++i)
            {
                programList_[i].SetStepNum(i);
            }
        }

    }
    else //sub item
    {
//        if(sIndex == 0) //sub item1 do nothing
//        {
//            return;
//        }
//        ICTopMoldUIItem *topItem = &programList_[gIndex].at(tIndex);
//        ICSubMoldUIItem *subItem = topItem->at(sIndex);
//        if(sIndex == 0 ||
//           sIndex == topItem->SubItemCount() - 1) //it's not work when select the oth or last subItem
//        {
//            return;
//        }
    }
//    isEdit_ = true;
    UpdateUIProgramList_();
    isModifyProgram_ = true;
}

void ICHCInstructionPageFrame::OnProgramChanged(int index, QString name)
{
    if(index < 0 || index > 8)
    {
        return;
    }
    isProgramChanged_ = SaveCurrentEdit();
    ui->moldContentListWidget->clear();
    programList_.clear();
    currentEdit_ = index;
//    ui->moldComboBox->setCurrentIndex(index);
    ui->programLabel->setText(name);
    UpdateHostParam();

}

bool ICHCInstructionPageFrame::SaveCurrentEdit()
{
    if(currentEdit_ == 0)
    {
        ICMold::CurrentMold()->SetMoldContent(ICMold::UIItemToMoldItem(programList_));
        ICMold::CurrentMold()->MoldReSum();
        return ICMold::CurrentMold()->SaveMoldFile();
    }
    else
    {
        ICMacroSubroutine::Instance()->SetSubRoutine(ICMold::UIItemToMoldItem(programList_), currentEdit_ - 1);
        ICMacroSubroutine::Instance()->SubRoutineResum(currentEdit_ - 1);
        bool ret = ICMacroSubroutine::Instance()->SaveMacroSubroutieFile(currentEdit_ - 1);
        QString moldName = ICParametersSave::Instance()->MoldName("Base.act");
        moldName.chop(3);
        moldName += "sub";
        moldName = QString("records/%1%2").arg(moldName).arg(currentEdit_ - 1);
        QFile::remove(moldName);
        ret =  ret && QFile::copy(QString("subs/sub%1.prg").arg(currentEdit_ - 1), moldName);
        return ret;
    }
}

void ICHCInstructionPageFrame::on_aPlusBtn_pressed()
{
    ICKeyboard::Instace()->SetKeyValue(ICKeyboard::VFB_AAdd);
    ICKeyboard::Instace()->SetPressed(true);
    ShowServoAction(ICKeyboard::VFB_AAdd);
}

void ICHCInstructionPageFrame::on_aMinusBtn_pressed()
{
    ICKeyboard::Instace()->SetKeyValue(ICKeyboard::VFB_ASub);
    ICKeyboard::Instace()->SetPressed(true);
    ShowServoAction(ICKeyboard::VFB_ASub);
}

void ICHCInstructionPageFrame::OnActionButtonReleased()
{
    ICKeyboard::Instace()->SetPressed(false);
}

void ICHCInstructionPageFrame::ShowServoAction(int key)
{
    if(!this->isHidden())
    {
        if(guidePage_)
        {
            if(guidePage_->isHidden())
            {
                ui->lineButton->click();
                actionPage_->KeyToActionCheck(key);
            }
            else
            {
                guidePage_->GuideKeyToActionCheck(key);
            }
        }
       else
        {
            ui->lineButton->click();
            actionPage_->KeyToActionCheck(key);
        }
    }

}

void  ICHCInstructionPageFrame::OnGuideFinished()
{
    ICMold::CurrentMold()->SetMoldContent(guidePage_->CreateCommand());
    UpdateHostParam();
    isModifyProgram_ = true;
}

void ICHCInstructionPageFrame::on_tryButton_clicked()
{
    //    if(!ICVirtualHost::GlobalVirtualHost()->IsOrigined())
    //    {
    //        QMessageBox::warning(this,
    //                             tr("Warning"),
    //                             tr("Has not been origin!"));
    //        return;
    //    }
        ICManualRun cmd;
        int currentStep = ui->moldContentListWidget->currentRow();
        int g,t,s;
        FindIndex_(currentStep, g, t, s);
        if(g >= programList_.size()) return;
    //    QList<ICMoldItem> moldItems = ICMold::UIItemToMoldItem(QList<ICGroupMoldUIItem>()<<programList_.at(g));
    //    if(moldItems.empty()) return;
    //    if(currentStep >= moldItems.size()) return;
        ICMoldItem item;
        if(s < 0)
        {
            item = programList_.at(g).at(t).ToMoldItems().at(0);
        }
        else
        {
            item = programList_.at(g).at(t).at(s).ToMoldItem();
        }
        cmd.SetSlave(1);
        cmd.SetGM(item.GMVal());
        cmd.SetNumber(currentStep);
        cmd.SetPoint(item.SubNum());
        cmd.SetPos(item.Pos());
        cmd.SetIFVal(item.IFVal());
        //    cmd.SetIFVal(1);
        if(ICCommandProcessor::Instance()->ExecuteCommand(cmd).toBool())
        {
    //        //        ++currentStep;
    //        //        currentStep %= mold->MoldContent().size();
    //        ICVirtualHost::GlobalVirtualHost()->SetHostStatus(ICVirtualHost::ActL, 1);
    //        ICVirtualHost::GlobalVirtualHost()->SetSingleRun(true);
    //        ui->singleButton->setEnabled(false);
        }

}

int ICHCInstructionPageFrame::ValidFlag()
{
    QVector<int> flags;
    ICMoldItem* item;
    int count;
    for(int i = 0; i != programList_.size(); ++i)
    {
        count = programList_.at(i).ItemCount();
        for(int j = 0; j != count; ++j)
        {
            item = programList_[i].MoldItemAt(j);
            if(item->Action() == ICMold::ACTCOMMENT)
            {
                flags.append(item->Flag());
            }
        }
    }
    qSort(flags);
    if(flags.isEmpty())
    {
        return 0;
    }
    if(flags.size() - 1 == flags.last())
    {
        return flags.size();
    }
    if(flags[0] != 0)
    {
        return 0;
    }
    for(int i = 1 ; i != flags.size(); ++i)
    {
        if(flags.at(i) - flags.at(i - 1) > 1)
        {
            return flags.at(i - 1) + 1;
        }
    }
    return 0;
}

QStringList ICHCInstructionPageFrame::Flags()
{
    QStringList selList;
    int count;
    ICMoldItem* item;
    for(int i = 0; i != programList_.size(); ++i)
    {
        count = programList_.at(i).ItemCount();
        for(int j = 0; j != count; ++j)
        {
            item = programList_[i].MoldItemAt(j);
            if(item->Action() == ICMold::ACTCOMMENT)
            {
                selList.append(QString(tr("Flag[%1]:%2")
                                       .arg(item->Flag())
                                       .arg(item->Comment())));
            }
        }
    }
    return selList;
}
