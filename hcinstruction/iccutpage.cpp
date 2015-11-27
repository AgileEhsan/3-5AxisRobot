#include <QPushButton>
#include "iccutpage.h"
#include "ui_iccutpage.h"

#include "icvirtualhost.h"
#include "icactioncommand.h"
#include "icvirtualkey.h"

ICCutPage::ICCutPage(QWidget *parent) :
    ICInstructionEditorBase(parent),
    ui(new Ui::ICCutPage),
    onPixmap_(":/resource/ledgreen(16).png"),
    offPixmap_(":/resource/ledgray(16).png")
{
    ui->setupUi(this);
    QPushButton *buttons = new QPushButton[ui->tableWidget->rowCount()];
    QPushButton * button;
//    ICLineEditWithVirtualNumericKeypad* delays = new ICLineEditWithVirtualNumericKeypad[ui->tableWidget->rowCount()];
//    ICLineEditWithVirtualNumericKeypad *delayEdit;
    ioNames_<<tr("Fixture1  ")<<tr("Fixture2  ")<<tr("Fixture3  ")<<tr("Fixture4  ")
           <<tr("Sucker1   ")<<tr("Sucker2   ")
          <<tr("Sucker3   ")
         <<tr("Sucker4   ")
          <<tr("Sucker-5  ")<<tr("Sucker-6  ")
         <<tr("Sucker-7  ")<<tr("Sucker-8  ");
    onClipToOffClip_.insert(ICMold::ACTCLIP1ON, ICMold::ACTCLIP1OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP2ON, ICMold::ACTCLIP2OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP3ON, ICMold::ACTCLIP3OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP4ON, ICMold::ACTCLIP4OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP5ON, ICMold::ACTCLIP5OFF);
    onClipToOffClip_.insert(ICMold::ACTCLIP6ON, ICMold::ACTCLIP6OFF);
    onClipToOffClip_.insert(ICMold::ACT_AUX1, ICMold::ACT_AUX1 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX2, ICMold::ACT_AUX2 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX3, ICMold::ACT_AUX3 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX4, ICMold::ACT_AUX4 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX5, ICMold::ACT_AUX5 + 1000);
    onClipToOffClip_.insert(ICMold::ACT_AUX6, ICMold::ACT_AUX6 + 1000);
//    onClipToOffClip_.insert(ICMold::ACTCLIP7ON, ICMold::ACTCLIP7OFF);
//    onClipToOffClip_.insert(ICMold::ACTCLIP8ON, ICMold::ACTCLIP8OFF);

    offClipToOnClip_.insert(ICMold::ACTCLIP1OFF, ICMold::ACTCLIP1ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP2OFF, ICMold::ACTCLIP2ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP3OFF, ICMold::ACTCLIP3ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP4OFF, ICMold::ACTCLIP4ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP5OFF, ICMold::ACTCLIP5ON);
    offClipToOnClip_.insert(ICMold::ACTCLIP6OFF, ICMold::ACTCLIP6ON);
    offClipToOnClip_.insert(ICMold::ACT_AUX1 + 1000, ICMold::ACT_AUX1);
    offClipToOnClip_.insert(ICMold::ACT_AUX2 + 1000, ICMold::ACT_AUX2);
    offClipToOnClip_.insert(ICMold::ACT_AUX3 + 1000, ICMold::ACT_AUX3);
    offClipToOnClip_.insert(ICMold::ACT_AUX4 + 1000, ICMold::ACT_AUX4);
    offClipToOnClip_.insert(ICMold::ACT_AUX5 + 1000, ICMold::ACT_AUX5);
    offClipToOnClip_.insert(ICMold::ACT_AUX6 + 1000, ICMold::ACT_AUX6);

//    offClipToOnClip_.insert(ICMold::ACTCLIP7OFF, ICMold::ACTCLIP7ON);
//    offClipToOnClip_.insert(ICMold::ACTCLIP8OFF, ICMold::ACTCLIP8ON);
    QList<uint> initStatus = onClipToOffClip_.values();
//    QList<uint> initStatus ;
//        initStatus << 16<< 17 << 18<< 19<< 20<< 21<< 13<< 14<< 15<<29
//                      << 30 << 31 << 22 << 23;

//    QIntValidator *validator = new QIntValidator(0, 2000, this);
    for(int i = 0; i != ui->tableWidget->rowCount(); ++i)
    {
        button = buttons + i;
        button->setIcon(offPixmap_);
        button->setText(ioNames_.at(i));

//        delayEdit = delays + i;
//        delayEdit->SetDecimalPlaces(1);
//        delayEdit->setValidator(validator);
//        delayEdit->setText("0.0");

        settingButtons_.append(button);
//        delayEdits_.append(delayEdit);
        ui->tableWidget->setCellWidget(i, 1, button);
//        ui->tableWidget->setCellWidget(i, 2, delayEdit);

        buttonToClip_.insert(button, initStatus.at(i));
        buttonSignalMapper_.setMapping(button, button);
        connect(button,
                SIGNAL(clicked()),
                &buttonSignalMapper_,
                SLOT(map()));
    }
#ifdef HC_SK_5
    ui->tableWidget->setColumnWidth(0, 36);
#endif

    ui->tableWidget->resizeColumnsToContents();

    commandKeyMap_.insert(settingButtons_.at(0), qMakePair(static_cast<int>(IC::VKEY_CLIP1ON), static_cast<int>(IC::VKEY_CLIP1OFF)));
    commandKeyMap_.insert(settingButtons_.at(1), qMakePair(static_cast<int>(IC::VKEY_CLIP2ON), static_cast<int>(IC::VKEY_CLIP2OFF)));
    commandKeyMap_.insert(settingButtons_.at(2), qMakePair(static_cast<int>(IC::VKEY_CLIP3ON), static_cast<int>(IC::VKEY_CLIP3OFF)));
    commandKeyMap_.insert(settingButtons_.at(3), qMakePair(static_cast<int>(IC::VKEY_CLIP4ON), static_cast<int>(IC::VKEY_CLIP4OFF)));
    commandKeyMap_.insert(settingButtons_.at(4), qMakePair(static_cast<int>(IC::VKEY_CLIP5ON), static_cast<int>(IC::VKEY_CLIP5OFF)));
    commandKeyMap_.insert(settingButtons_.at(5), qMakePair(static_cast<int>(IC::VKEY_CLIP6ON), static_cast<int>(IC::VKEY_CLIP6OFF)));
    commandKeyMap_.insert(settingButtons_.at(6), qMakePair(static_cast<int>(IC::VKEY_RESERVE1_ON), static_cast<int>(IC::VKEY_RESERVE1_OFF)));
    commandKeyMap_.insert(settingButtons_.at(7), qMakePair(static_cast<int>(IC::VKEY_RESERVE2_ON), static_cast<int>(IC::VKEY_RESERVE2_OFF)));
    commandKeyMap_.insert(settingButtons_.at(8), qMakePair(static_cast<int>(IC::VKEY_RESERVE3_ON), static_cast<int>(IC::VKEY_RESERVE3_OFF)));
    commandKeyMap_.insert(settingButtons_.at(9), qMakePair(static_cast<int>(IC::VKEY_RESERVE4_ON), static_cast<int>(IC::VKEY_RESERVE4_OFF)));
    commandKeyMap_.insert(settingButtons_.at(10), qMakePair(static_cast<int>(IC::VKEY_RESERVE5_ON), static_cast<int>(IC::VKEY_RESERVE5_OFF)));
    commandKeyMap_.insert(settingButtons_.at(11), qMakePair(static_cast<int>(IC::VKEY_RESERVE6_ON), static_cast<int>(IC::VKEY_RESERVE6_OFF)));
//    commandKeyMap_.insert(settingButtons_.at(12), qMakePair(static_cast<int>(IC::VKEY_CLIP7ON), static_cast<int>(IC::VKEY_CLIP7OFF)));
//    commandKeyMap_.insert(settingButtons_.at(13), qMakePair(static_cast<int>(IC::VKEY_CLIP8ON), static_cast<int>(IC::VKEY_CLIP8OFF)));

    connect(&buttonSignalMapper_,
            SIGNAL(mapped(QWidget*)),
            this,
            SLOT(CommandButtonClicked(QWidget*)));
}

ICCutPage::~ICCutPage()
{
    delete ui;
}
void ICCutPage::showEvent(QShowEvent *e)
{
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        ui->tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
    }
    connect(ICVirtualHost::GlobalVirtualHost(),
            SIGNAL(StatusRefreshed()),
            this,
            SLOT(StatusRefreshed()));
    QWidget::showEvent(e);
}

void ICCutPage::hideEvent(QHideEvent *e)
{
    disconnect(ICVirtualHost::GlobalVirtualHost(),
               SIGNAL(StatusRefreshed()),
               this,
               SLOT(StatusRefreshed()));
    QWidget::hideEvent(e);
}

void ICCutPage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        ioNames_.clear();
        ioNames_<<tr("Fixture1  ")<<tr("Fixture2  ")<<tr("Fixture3  ")<<tr("Fixture4  ")
               <<tr("Sucker1   ")<<tr("Sucker2   ")
              <<tr("Sucker3   ")
             <<tr("Sucker4   ")
              <<tr("Sucker-5  ")<<tr("Sucker-6  ")
             <<tr("Sucker-7  ")<<tr("Sucker-8  ");
        for(int i = 0; i != settingButtons_.size(); ++i)
        {
            settingButtons_[i]->setText(ioNames_.at(i));
        }
        break;
    default:
        break;
    }
}

void ICCutPage::SyncStatusImpl(const QList<ICMoldItem> &items)
{
//    Q_UNUSED(items)
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        ui->tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
    }
    ICMoldItem item;
//    ICLineEditWithVirtualNumericKeypad* time;
    QPushButton* button;
    int row;
    for(int i = 0; i < items.size(); ++i)
    {
        item = items.at(i);
        row = item.SVal();
        if(row >= ui->tableWidget->rowCount()) continue;
        ui->tableWidget->item(row, 0)->setCheckState(Qt::Checked);
        ui->tableWidget->scrollToItem(ui->tableWidget->item(row, 0));
        button = qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(row, 1));
//        button->setChecked(item.IFVal());
        int currentClip = buttonToClip_.value(button);
//        if(item.IFVal())
//        {
//            if(!onClipToOffClip_.contains(currentClip))
//                button->click();
//        }
//        else
//        {
//            if(!offClipToOnClip_.contains(currentClip))
//                button->click();
//        }
//        time = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(ui->tableWidget->cellWidget(row, 2));
//        time->SetThisIntToThisText(item.DVal());
    }
}


void ICCutPage::StatusRefreshed()
{
//    static ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
//    QMap<QLabel*, int>::iterator p = currentPosMap_.begin();
//    while(p != currentPosMap_.end())
//    {
//        if(host->IsClipOn(p.value()))
//        {
//            if(!ledIsOnMap_.value(p.key()))
//            {
//                p.key()->setPixmap(onPixmap_);
//                ledIsOnMap_.insert(p.key(), true);
//            }
//        }
//        else
//        {
//            if(ledIsOnMap_.value(p.key()))
//            {
//                p.key()->setPixmap(offPixmap_);
//                ledIsOnMap_.insert(p.key(), false);
//            }
//        }
//        ++p;
//    }
}

void ICCutPage::CommandButtonClicked(QWidget *widget)
{
    QAbstractButton* button = qobject_cast<QAbstractButton*>(widget);
    Q_ASSERT_X(button != NULL, "ICCutPage::CommandButtonClicked", "widget is null");
    int currentClip = buttonToClip_.value(button);
    if(onClipToOffClip_.contains(currentClip))
    {
//        int key = commandKeyMap_.value(button).second;
        buttonToClip_.insert(button, onClipToOffClip_.value(currentClip));
        button->setIcon(offPixmap_);
    }
    else
    {
//        key = commandKeyMap_.value(button).first;
        buttonToClip_.insert(button, offClipToOnClip_.value(currentClip));
        button->setIcon(onPixmap_);
    }
//    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(key);
}


QList<ICMoldItem> ICCutPage::CreateCommandImpl() const
{
    QList<ICMoldItem> ret;
    ICMoldItem item;
    uint val;
    for(int i = 0; i != ui->tableWidget->rowCount(); ++i)
    {
        if(ui->tableWidget->item(i,0)->checkState() == Qt::Checked)
        {
            val = buttonToClip_.value(qobject_cast<QAbstractButton*>(ui->tableWidget->cellWidget(i, 1)));
            if(onClipToOffClip_.contains(val))
            {
                item.SetIFVal(1);
            }
            else
            {
                item.SetIFVal(0);
            }
            item.SetSVal(i);
            item.SetAction(ICMold::ACT_Cut);
//            item.SetIFVal(buttonToClip_.value())
//            item.SetDVal(delayEdits_.at(i)->TransThisTextToThisInt());
            ret.append(item);
        }
    }
    return ret;
}

void ICCutPage::on_goToAxis_clicked()
{
    emit GoToAxis();
}

void ICCutPage::on_goToFixture_clicked()
{
    emit GoToFixture();
}
