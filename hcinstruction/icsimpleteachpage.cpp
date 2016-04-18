#include "icsimpleteachpage.h"
#include "ui_icsimpleteachpage.h"
#include "config.h"
#include <QDebug>

ICSimpleTeachPage::ICSimpleTeachPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICSimpleTeachPage)
{
    ui->setupUi(this);

    fixtureSel_ = new ICGuideFixtureEditor();
    fixtureSel_->hide();

    posValidator_.setRange(0, 655300);
    speedValidator_.setRange(0, 100);
    delayValidator_.setRange(0, 30000);

    ui->stdPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->stdPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->stdPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->stdPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->stdPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->getProductPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->getProductPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->getProductPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->getProductPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->getProductPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->getOutletPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->getOutletPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->getOutletPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->getOutletPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->getOutletPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->posBHorX1->SetDecimalPlaces(POS_DECIMAL);
    ui->posBHorY1->SetDecimalPlaces(POS_DECIMAL);
    ui->posBHorZ->SetDecimalPlaces(POS_DECIMAL);
    ui->posBHorX2->SetDecimalPlaces(POS_DECIMAL);
    ui->posBHorY2->SetDecimalPlaces(POS_DECIMAL);

    ui->releaseProductPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseProductPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseProductPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseProductPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseProductPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->releaseOutletPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseOutletPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseOutletPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseOutletPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseOutletPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->cutOutletPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->cutOutletPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->cutOutletPosZ->SetDecimalPlaces(POS_DECIMAL);


    ui->stdPosX1->setValidator(&posValidator_);
    ui->stdPosY1->setValidator(&posValidator_);
    ui->stdPosZ->setValidator(&posValidator_);
    ui->stdPosX2->setValidator(&posValidator_);
    ui->stdPosY2->setValidator(&posValidator_);

    ui->getProductPosX1->setValidator(&posValidator_);
    ui->getProductPosY1->setValidator(&posValidator_);
    ui->getProductPosZ->setValidator(&posValidator_);
    ui->getProductPosX2->setValidator(&posValidator_);
    ui->getProductPosY2->setValidator(&posValidator_);

    ui->getOutletPosX1->setValidator(&posValidator_);
    ui->getOutletPosY1->setValidator(&posValidator_);
    ui->getOutletPosZ->setValidator(&posValidator_);
    ui->getOutletPosX2->setValidator(&posValidator_);
    ui->getOutletPosY2->setValidator(&posValidator_);

    ui->posBHorX1->setValidator(&posValidator_);
    ui->posBHorY1->setValidator(&posValidator_);
    ui->posBHorZ->setValidator(&posValidator_);
    ui->posBHorX2->setValidator(&posValidator_);
    ui->posBHorY2->setValidator(&posValidator_);

    ui->releaseProductPosX1->setValidator(&posValidator_);
    ui->releaseProductPosY1->setValidator(&posValidator_);
    ui->releaseProductPosZ->setValidator(&posValidator_);
    ui->releaseProductPosX2->setValidator(&posValidator_);
    ui->releaseProductPosY2->setValidator(&posValidator_);

    ui->releaseOutletPosX1->setValidator(&posValidator_);
    ui->releaseOutletPosY1->setValidator(&posValidator_);
    ui->releaseOutletPosZ->setValidator(&posValidator_);
    ui->releaseOutletPosX2->setValidator(&posValidator_);
    ui->releaseOutletPosY2->setValidator(&posValidator_);

    ui->cutOutletPosX1->setValidator(&posValidator_);
    ui->cutOutletPosY1->setValidator(&posValidator_);
    ui->cutOutletPosZ->setValidator(&posValidator_);


    ui->stdSpeedX1->setValidator(&speedValidator_);
    ui->stdSpeedY1->setValidator(&speedValidator_);
    ui->stdSpeedZ->setValidator(&speedValidator_);
    ui->stdSpeedX2->setValidator(&speedValidator_);
    ui->stdSpeedY2->setValidator(&speedValidator_);

    ui->getProductSpeedX1->setValidator(&speedValidator_);
    ui->getProductSpeedY1->setValidator(&speedValidator_);
    ui->getProductSpeedZ->setValidator(&speedValidator_);
    ui->getProductSpeedX2->setValidator(&speedValidator_);
    ui->getProductSpeedY2->setValidator(&speedValidator_);

    ui->getOutletSpeedX1->setValidator(&speedValidator_);
    ui->getOutletSpeedY1->setValidator(&speedValidator_);
    ui->getOutletSpeedZ->setValidator(&speedValidator_);
    ui->getOutletSpeedX2->setValidator(&speedValidator_);
    ui->getOutletSpeedY2->setValidator(&speedValidator_);

    ui->speedBHorX1->setValidator(&speedValidator_);
    ui->speedBHorY1->setValidator(&speedValidator_);
    ui->speedBHorZ->setValidator(&speedValidator_);
    ui->speedBHorX2->setValidator(&speedValidator_);
    ui->speedBHorY2->setValidator(&speedValidator_);

    ui->cutOnTime->SetDecimalPlaces(2);
    ui->cutOnTime->setValidator(&delayValidator_);

}

ICSimpleTeachPage::~ICSimpleTeachPage()
{
    delete ui;
}

void ICSimpleTeachPage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ICSimpleTeachPage::showEvent(QShowEvent *e)
{
    ui->posInsideBtn->setChecked(true);

    stData_ = ICMold::CurrentMold()->GetSimpleTeachData();
    ui->mainArmEn->setChecked(stData_->usedMainArm);
    ui->mainArmOutletEn->setChecked(stData_->usedMainArmOutlet);
    ui->subArmEn->setChecked(stData_->usedSubArm);
    ui->cutOutletEn->setChecked(stData_->usedCutOutlet);

    ui->stdPosX1->SetThisIntToThisText(stData_->stdPos.b.x1);
    ui->stdPosY1->SetThisIntToThisText(stData_->stdPos.b.y1);
    ui->stdPosZ->SetThisIntToThisText(stData_->stdPos.b.z);
    ui->stdPosX2->SetThisIntToThisText(stData_->stdPos.b.x2);
    ui->stdPosY2->SetThisIntToThisText(stData_->stdPos.b.y2);
    ui->stdSpeedX1->SetThisIntToThisText(stData_->stdPos.b.x1S);
    ui->stdSpeedY1->SetThisIntToThisText(stData_->stdPos.b.y1S);
    ui->stdSpeedZ->SetThisIntToThisText(stData_->stdPos.b.zS);
    ui->stdSpeedX2->SetThisIntToThisText(stData_->stdPos.b.x2S);
    ui->stdSpeedY2->SetThisIntToThisText(stData_->stdPos.b.y2S);


    ui->getProductPosX1->SetThisIntToThisText(stData_->getProductPos.pos.b.x1);
    ui->getProductPosY1->SetThisIntToThisText(stData_->getProductPos.pos.b.y1);
    ui->getProductPosZ->SetThisIntToThisText(stData_->getProductPos.pos.b.z);
    ui->getProductPosX2->SetThisIntToThisText(stData_->getProductPos.pos.b.x2);
    ui->getProductPosY2->SetThisIntToThisText(stData_->getProductPos.pos.b.y2);
    ui->getProductSpeedX1->SetThisIntToThisText(stData_->getProductPos.pos.b.x1S);
    ui->getProductSpeedY1->SetThisIntToThisText(stData_->getProductPos.pos.b.y1S);
    ui->getProductSpeedZ->SetThisIntToThisText(stData_->getProductPos.pos.b.zS);
    ui->getProductSpeedX2->SetThisIntToThisText(stData_->getProductPos.pos.b.x2S);
    ui->getProductSpeedY2->SetThisIntToThisText(stData_->getProductPos.pos.b.y2S);
    ui->getProductFInfo->setText(fixtureSel_->SelectedNames(stData_->getProductPos.fixtureConfis).join(","));

    ui->getOutletPosX1->SetThisIntToThisText(stData_->getOutletPos.pos.b.x1);
    ui->getOutletPosY1->SetThisIntToThisText(stData_->getOutletPos.pos.b.y1);
    ui->getOutletPosZ->SetThisIntToThisText(stData_->getOutletPos.pos.b.z);
    ui->getOutletPosX2->SetThisIntToThisText(stData_->getOutletPos.pos.b.x2);
    ui->getOutletPosY2->SetThisIntToThisText(stData_->getOutletPos.pos.b.y2);
    ui->getOutletSpeedX1->SetThisIntToThisText(stData_->getOutletPos.pos.b.x1S);
    ui->getOutletSpeedY1->SetThisIntToThisText(stData_->getOutletPos.pos.b.y1S);
    ui->getOutletSpeedZ->SetThisIntToThisText(stData_->getOutletPos.pos.b.zS);
    ui->getOutletSpeedX2->SetThisIntToThisText(stData_->getOutletPos.pos.b.x2S);
    ui->getOutletSpeedY2->SetThisIntToThisText(stData_->getOutletPos.pos.b.y2S);
    ui->getOutletFInfo->setText(fixtureSel_->SelectedNames(stData_->getOutletPos.fixtureConfis).join(","));

    ui->posBHorX1->SetThisIntToThisText(stData_->posBH.b.x1);
    ui->posBHorY1->SetThisIntToThisText(stData_->posBH.b.y1);
    ui->posBHorZ->SetThisIntToThisText(stData_->posBH.b.z);
    ui->posBHorX2->SetThisIntToThisText(stData_->posBH.b.x2);
    ui->posBHorY2->SetThisIntToThisText(stData_->posBH.b.y2);
    ui->speedBHorX1->SetThisIntToThisText(stData_->posBH.b.x1S);
    ui->speedBHorY1->SetThisIntToThisText(stData_->posBH.b.y1S);
    ui->speedBHorZ->SetThisIntToThisText(stData_->posBH.b.zS);
    ui->speedBHorX2->SetThisIntToThisText(stData_->posBH.b.x2S);
    ui->speedBHorY2->SetThisIntToThisText(stData_->posBH.b.y2S);

    for(int i = 0; i < stData_->releaseProductPosList.size(); ++i)
    {
        ReleasePosData posData = stData_->releaseProductPosList.at(i);
        ui->releasePosView->addItem(PosDataToString(posData));

        AddPosHelper(ui->releaseProductSpeedGroup, releaseProductSpeedUI, tr("Rel Product"));
        PosSpeedUIWidgets tmp = releaseProductSpeedUI.last();
        tmp.b.x1SpeedEdit->SetThisIntToThisText(posData.pos.b.x1S);
        tmp.b.y1SpeedEdit->SetThisIntToThisText(posData.pos.b.y1S);
        tmp.b.zSpeedEdit->SetThisIntToThisText(posData.pos.b.zS);
        tmp.b.x2SpeedEdit->SetThisIntToThisText(posData.pos.b.x2S);
        tmp.b.y2SpeedEdit->SetThisIntToThisText(posData.pos.b.y2S);

    }

    for(int i = 0; i < stData_->releaseOutletPosList.size(); ++i)
    {
        ReleasePosData posData = stData_->releaseOutletPosList.at(i);
        ui->releaseOutletView->addItem(PosDataToString(posData));

        AddPosHelper(ui->releaseOutletSpeedGroup, releaseOutletSpeedUI, tr("Rel Outlet"));
        PosSpeedUIWidgets tmp = releaseOutletSpeedUI.last();
        tmp.b.x1SpeedEdit->SetThisIntToThisText(posData.pos.b.x1S);
        tmp.b.y1SpeedEdit->SetThisIntToThisText(posData.pos.b.y1S);
        tmp.b.zSpeedEdit->SetThisIntToThisText(posData.pos.b.zS);
        tmp.b.x2SpeedEdit->SetThisIntToThisText(posData.pos.b.x2S);
        tmp.b.y2SpeedEdit->SetThisIntToThisText(posData.pos.b.y2S);

    }

    for(int i = 0; i < stData_->cutOutletPosList.size(); ++i)
    {
        ReleasePosData posData = stData_->cutOutletPosList.at(i);
        ui->cutPosView->addItem(PosDataToString(posData));

        AddPosHelper(ui->cutOutletSpeedGroup, cutOutletSpeedUI, tr("Cut Pos"));
        PosSpeedUIWidgets tmp = cutOutletSpeedUI.last();
        tmp.b.x1SpeedEdit->SetThisIntToThisText(posData.pos.b.x1S);
        tmp.b.y1SpeedEdit->SetThisIntToThisText(posData.pos.b.y1S);
        tmp.b.zSpeedEdit->SetThisIntToThisText(posData.pos.b.zS);
        tmp.b.x2SpeedEdit->SetThisIntToThisText(posData.pos.b.x2S);
        tmp.b.y2SpeedEdit->SetThisIntToThisText(posData.pos.b.y2S);
    }

    on_mainArmEn_toggled(ui->mainArmEn->isChecked());
    on_mainArmOutletEn_toggled(ui->mainArmOutletEn->isChecked());
    on_subArmEn_toggled(ui->subArmEn->isChecked());
    on_cutOutletEn_toggled(ui->cutOutletEn->isChecked());

    QWidget::showEvent(e);
}

void ICSimpleTeachPage::on_posOutsideBtn_toggled(bool checked)
{
    if(checked)
        ui->posPageContainer->setCurrentIndex(1);
}

void ICSimpleTeachPage::on_posOfCutBtn_toggled(bool checked)
{
    if(checked)
        ui->posPageContainer->setCurrentIndex(2);

}

void ICSimpleTeachPage::on_posInsideBtn_toggled(bool checked)
{
    if(checked)
        ui->posPageContainer->setCurrentIndex(0);
}

void ICSimpleTeachPage::on_mainArmEn_toggled(bool checked)
{
    ui->cutOutletEn->setEnabled(checked);
    SetMainArmPosEnabled(checked || ui->mainArmOutletEn->isChecked());
    SetReleaseProductEnabled(checked);
}

void ICSimpleTeachPage::on_mainArmOutletEn_toggled(bool checked)
{
    if(checked)
        ui->subArmEn->setChecked(false);
    SetMainArmPosEnabled(checked || ui->mainArmEn->isChecked());
    SetReleaseOutletEnabled(checked || ui->subArmEn->isChecked());

}

void ICSimpleTeachPage::on_subArmEn_toggled(bool checked)
{
    if(checked)
        ui->mainArmOutletEn->setChecked(false);
    SetSubArmPosEnabled(checked);
    SetReleaseOutletEnabled(checked || ui->mainArmOutletEn->isChecked());
}

void ICSimpleTeachPage::SetMainArmPosEnabled(bool en)
{
    ui->stdPosX1->setVisible(en);
    ui->stdPosY1->setVisible(en);

    ui->getProductPosX1->setVisible(en);
    ui->getProductPosY1->setVisible(en);

    ui->getOutletPosX1->setVisible(en);
    ui->getOutletPosY1->setVisible(en);

    ui->posBHorX1->setVisible(en);
    ui->posBHorY1->setVisible(en);

    ui->releaseProductPosX1->setVisible(en);
    ui->releaseProductPosY1->setVisible(en);

    ui->releaseOutletPosX1->setVisible(en);
    ui->releaseOutletPosY1->setVisible(en);

    ui->cutOutletPosX1->setVisible(en);
    ui->cutOutletPosY1->setVisible(en);

    ui->stdSpeedX1->setVisible(en);
    ui->stdSpeedY1->setVisible(en);
    ui->getProductSpeedX1->setVisible(en);
    ui->getProductSpeedY1->setVisible(en);
    ui->getOutletSpeedX1->setVisible(en);
    ui->getOutletSpeedY1->setVisible(en);
    ui->speedBHorX1->setVisible(en);
    ui->speedBHorY1->setVisible(en);

    ui->pIX1Label->setVisible(en);
    ui->pIX1Label_2->setVisible(en);
    ui->pIX1Label_3->setVisible(en);
    ui->pIX1Label_4->setVisible(en);
    ui->pIX1mmLabel->setVisible(en);
    ui->pIX1mmLabel_2->setVisible(en);
    ui->pIX1mmLabel_3->setVisible(en);
    ui->pIX1SpeedLabel->setVisible(en);


    ui->pIY1Label->setVisible(en);
    ui->pIY1Label_2->setVisible(en);
    ui->pIY1Label_3->setVisible(en);
    ui->pIY1Label_4->setVisible(en);
    ui->pIY1mmLabel->setVisible(en);
    ui->pIY1mmLabel_2->setVisible(en);
    ui->pIY1mmLabel_3->setVisible(en);
    ui->pIY1SpeedLabel->setVisible(en);

    PosSpeedUIWidgets speedUI;
    for(int i = 0; i < releaseProductSpeedUI.size(); ++i)
    {
        speedUI = releaseProductSpeedUI.at(i);
        speedUI.b.x1SpeedEdit->setVisible(en);
        speedUI.b.y1SpeedEdit->setVisible(en);
    }

    for(int i = 0; i < releaseOutletSpeedUI.size(); ++i)
    {
        speedUI = releaseOutletSpeedUI.at(i);
        speedUI.b.x1SpeedEdit->setVisible(en);
        speedUI.b.y1SpeedEdit->setVisible(en);
    }

    for(int i = 0; i < cutOutletSpeedUI.size(); ++i)
    {
        speedUI = cutOutletSpeedUI.at(i);
        speedUI.b.x1SpeedEdit->setVisible(en);
        speedUI.b.y1SpeedEdit->setVisible(en);
    }
}

void ICSimpleTeachPage::SetSubArmPosEnabled(bool en)
{
    ui->stdPosX2->setVisible(en);
    ui->stdPosY2->setVisible(en);

    ui->getProductPosX2->setVisible(en);
    ui->getProductPosY2->setVisible(en);

    ui->getOutletPosX2->setVisible(en);
    ui->getOutletPosY2->setVisible(en);

    ui->posBHorX2->setVisible(en);
    ui->posBHorY2->setVisible(en);

    ui->releaseProductPosX2->setVisible(en);
    ui->releaseProductPosY2->setVisible(en);

    ui->releaseOutletPosX2->setVisible(en);
    ui->releaseOutletPosY2->setVisible(en);

    ui->stdSpeedX2->setVisible(en);
    ui->stdSpeedY2->setVisible(en);
    ui->getProductSpeedX2->setVisible(en);
    ui->getProductSpeedY2->setVisible(en);
    ui->getOutletSpeedX2->setVisible(en);
    ui->getOutletSpeedY2->setVisible(en);
    ui->speedBHorX2->setVisible(en);
    ui->speedBHorY2->setVisible(en);

    ui->pIX2Label->setVisible(en);
    ui->pIX2Label_2->setVisible(en);
    ui->pIX2Label_3->setVisible(en);
    ui->pIX2mmLabel->setVisible(en);
    ui->pIX2mmLabel_2->setVisible(en);
    ui->pIX2SpeedLabel->setVisible(en);

    ui->pIY2Label->setVisible(en);
    ui->pIY2Label_2->setVisible(en);
    ui->pIY2Label_3->setVisible(en);
    ui->pIY2mmLabel->setVisible(en);
    ui->pIY2mmLabel_2->setVisible(en);
    ui->pIY2SpeedLabel->setVisible(en);

    PosSpeedUIWidgets speedUI;
    for(int i = 0; i < releaseProductSpeedUI.size(); ++i)
    {
        speedUI = releaseProductSpeedUI.at(i);
        speedUI.b.x2SpeedEdit->setVisible(en);
        speedUI.b.y2SpeedEdit->setVisible(en);
    }

    for(int i = 0; i < releaseOutletSpeedUI.size(); ++i)
    {
        speedUI = releaseOutletSpeedUI.at(i);
        speedUI.b.x2SpeedEdit->setVisible(en);
        speedUI.b.y2SpeedEdit->setVisible(en);
    }

    for(int i = 0; i < cutOutletSpeedUI.size(); ++i)
    {
        speedUI = cutOutletSpeedUI.at(i);
        speedUI.b.x2SpeedEdit->setVisible(en);
        speedUI.b.y2SpeedEdit->setVisible(en);
    }
}

void ICSimpleTeachPage::SetReleaseOutletEnabled(bool en)
{
    ui->label_14->setVisible(en);
    ui->getOutletFInfo->setVisible(en);
    ui->getOutletFSel->setVisible(en);
    ui->getOutletPosSetIn->setVisible(en);
    ui->getOutletPosX1->setVisible(en);
    ui->getOutletPosX2->setVisible(en);
    ui->getOutletPosY1->setVisible(en);
    ui->getOutletPosY2->setVisible(en);
    ui->getOutletPosZ->setVisible(en);
    ui->getOutletSpeedX1->setVisible(en);
    ui->getOutletSpeedX2->setVisible(en);
    ui->getOutletSpeedY1->setVisible(en);
    ui->getOutletSpeedY2->setVisible(en);
    ui->getOutletSpeedZ->setVisible(en);
    ui->label_22->setVisible(en);


    ui->label_3->setVisible(en);
    ui->releaseOutletCFInfo->setVisible(en);
    ui->releaseOutletFSel->setVisible(en);
    ui->releaseOutletPosX1->setVisible(en);
    ui->releaseOutletPosX2->setVisible(en);
    ui->releaseOutletPosY1->setVisible(en);
    ui->releaseOutletPosY2->setVisible(en);
    ui->releaseOutletPosZ->setVisible(en);
    ui->releaseOutletView->setVisible(en);
    ui->releaseOutletPosSetIn->setVisible(en);
    ui->addOutletPos->setVisible(en);
    ui->modifyOutletPos->setVisible(en);
    ui->deleteOutletPos->setVisible(en);
    for(int i = 0; i < releaseOutletSpeedUI.size(); ++i)
    {
        releaseOutletSpeedUI[i].b.posName->setVisible(en);
        releaseOutletSpeedUI[i].b.x1SpeedEdit->setVisible(en);
        releaseOutletSpeedUI[i].b.y1SpeedEdit->setVisible(en);
        releaseOutletSpeedUI[i].b.zSpeedEdit->setVisible(en);
        releaseOutletSpeedUI[i].b.x2SpeedEdit->setVisible(en);
        releaseOutletSpeedUI[i].b.y2SpeedEdit->setVisible(en);

    }
}

void ICSimpleTeachPage::SetReleaseProductEnabled(bool en)
{
    ui->label_21->setVisible(en);
    ui->getProductFInfo->setVisible(en);
    ui->getProductFSel->setVisible(en);
    ui->getProductPosSetIn->setVisible(en);
    ui->getProductPosX1->setVisible(en);
    ui->getProductPosY1->setVisible(en);
    ui->getProductPosZ->setVisible(en);
    ui->getProductPosX2->setVisible(en);
    ui->getProductPosY2->setVisible(en);
    ui->getProductSpeedX1->setVisible(en);
    ui->getProductSpeedY1->setVisible(en);
    ui->getProductSpeedZ->setVisible(en);
    ui->getProductSpeedX2->setVisible(en);
    ui->getProductSpeedY2->setVisible(en);
    ui->label->setVisible(en);



    ui->label_2->setVisible(en);
    ui->releasePosView->setVisible(en);
    ui->releaseProductCFInfo->setVisible(en);
    ui->releaseProductFSel->setVisible(en);
    ui->releaseProductPosSetIn->setVisible(en);
    ui->releaseProductPosX1->setVisible(en);
    ui->releaseProductPosY1->setVisible(en);
    ui->releaseProductPosZ->setVisible(en);
    ui->releaseProductPosX2->setVisible(en);
    ui->releaseProductPosY2->setVisible(en);
    ui->addProductPos->setVisible(en);
    ui->modifyProductPos->setVisible(en);
    ui->deleteProductPos->setVisible(en);
    for(int i = 0; i < releaseProductSpeedUI.size(); ++i)
    {
        releaseProductSpeedUI[i].b.posName->setVisible(en);
        releaseProductSpeedUI[i].b.x1SpeedEdit->setVisible(en);
        releaseProductSpeedUI[i].b.y1SpeedEdit->setVisible(en);
        releaseProductSpeedUI[i].b.zSpeedEdit->setVisible(en);
        releaseProductSpeedUI[i].b.x2SpeedEdit->setVisible(en);
        releaseProductSpeedUI[i].b.y2SpeedEdit->setVisible(en);

    }
}

void ICSimpleTeachPage::SetCutOutletEnabled(bool en)
{
    ui->posOfCutBtn->setVisible(en);

    for(int i = 0; i < cutOutletSpeedUI.size(); ++i)
    {
        cutOutletSpeedUI[i].b.posName->setVisible(en);
        cutOutletSpeedUI[i].b.x1SpeedEdit->setVisible(en);
        cutOutletSpeedUI[i].b.y1SpeedEdit->setVisible(en);
        cutOutletSpeedUI[i].b.zSpeedEdit->setVisible(en);
        cutOutletSpeedUI[i].b.x2SpeedEdit->setVisible(en);
        cutOutletSpeedUI[i].b.y2SpeedEdit->setVisible(en);

    }
}

bool ICSimpleTeachPage::UsedMainArm() const
{
    return ui->mainArmEn->isChecked() || ui->mainArmOutletEn->isChecked();
}

bool ICSimpleTeachPage::UsedSubArm() const
{
    return ui->subArmEn->isChecked();
}

bool ICSimpleTeachPage::UsedReleaseOutlet() const
{
    return ui->subArmEn->isChecked() || ui->mainArmOutletEn->isChecked();
}

QString ICSimpleTeachPage::PosDataToString(const ReleasePosData &posData, bool noSubArm,  const QString& dataName) const
{
    QString ret;
    AxisPosData data = posData.pos;
    if(UsedMainArm())
        ret += QString(tr("X1:%1, Y1:%2, ")).arg(QString::number(data.b.x1 / 100.0, 'f', 2))
                .arg(QString::number(data.b.y1 / 100.0, 'f', 2));
    ret += QString(tr("Z:%1\n")).arg(QString::number(data.b.z / 100.0, 'f', 2));
    if(UsedSubArm() && !noSubArm)
        ret += QString(tr(", X2:%1, Y2:%2")).arg(QString::number(data.b.x2 / 100.0, 'f', 2))
                .arg(QString::number(data.b.y2 / 100.0, 'f', 2));
    ret += tr("Use") + fixtureSel_->SelectedNames(posData.fixtureConfis).join(",");
    return ret;

}

ICLineEditWithVirtualNumericKeypad* CreateSpeedEdit(int speed, const QValidator* v)
{
    ICLineEditWithVirtualNumericKeypad* tmp = new ICLineEditWithVirtualNumericKeypad();
    tmp->SetDecimalPlaces(0);
    tmp->setValidator(v);
    tmp->SetThisIntToThisText(speed);
    tmp->setMinimumHeight( 30);
    tmp->setMaximumHeight(30);

    return tmp;
}

void ICSimpleTeachPage::AddPosHelper(QGridLayout *layout, QList<PosSpeedUIWidgets> &speedUI, const QString& posName, int defaultSpeed)
{
    int toInsertRow = speedUI.size();
    PosSpeedUIWidgets tmp;
    tmp.b.posName = new QLabel(QString(tr("%2-%1")).arg(toInsertRow + 1).arg(posName));
    tmp.b.posName->setMinimumWidth(ui->label_20->minimumWidth());
    tmp.b.posName->setMaximumWidth(ui->label_20->maximumWidth());
    tmp.b.x1SpeedEdit = CreateSpeedEdit(defaultSpeed, &speedValidator_);
    tmp.b.y1SpeedEdit = CreateSpeedEdit(defaultSpeed, &speedValidator_);
    tmp.b.zSpeedEdit = CreateSpeedEdit(defaultSpeed, &speedValidator_);
    tmp.b.x2SpeedEdit = CreateSpeedEdit(defaultSpeed, &speedValidator_);
    tmp.b.y2SpeedEdit = CreateSpeedEdit(defaultSpeed, &speedValidator_);
    speedUI.append(tmp);
    for(int i = 0; i < 6; ++i)
        layout->addWidget(tmp.all[i], toInsertRow, i);
}

void ICSimpleTeachPage::DelPosHelper(int row, QGridLayout *layout, QList<PosSpeedUIWidgets> &speedUI, const QString &posName)
{
    PosSpeedUIWidgets toDel = speedUI.at(row);
    for(int i = 0;i < 6; ++i)
    {
        layout->removeWidget(toDel.all[i]);
        toDel.all[i]->close();
        toDel.all[i]->deleteLater();
    }
    speedUI.removeAt(row);
    for(int i = row; i < speedUI.size(); ++i)
    {
        speedUI[i].b.posName->setText(QString(tr("%2-%1")).arg(i + 1).arg(posName));
    }
}

void ICSimpleTeachPage::on_addProductPos_clicked()
{
    ReleasePosData posData;
    posData.pos.b.x1 = ui->releaseProductPosX1->TransThisTextToThisInt();
    posData.pos.b.y1 = ui->releaseProductPosY1->TransThisTextToThisInt();
    posData.pos.b.z = ui->releaseProductPosZ->TransThisTextToThisInt();
    posData.pos.b.x2 = ui->releaseProductPosX2->TransThisTextToThisInt();
    posData.pos.b.y2 = ui->releaseProductPosY2->TransThisTextToThisInt();
    posData.fixtureConfis = releaseProductCFConfigs_;
    stData_->releaseProductPosList.append(posData);
    ui->releasePosView->addItem(PosDataToString(posData));

    AddPosHelper(ui->releaseProductSpeedGroup, releaseProductSpeedUI, tr("Rel Product"), posData.pos.b.x1S);
}



void ICSimpleTeachPage::on_modifyProductPos_clicked()
{
    QList<QListWidgetItem*> selected = ui->releasePosView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->releasePosView->row(selected.at(0));
    ReleasePosData posData = stData_->releaseProductPosList.at(toModifyIndex);
    posData.pos.b.x1 = ui->releaseProductPosX1->TransThisTextToThisInt();
    posData.pos.b.y1 = ui->releaseProductPosY1->TransThisTextToThisInt();
    posData.pos.b.z = ui->releaseProductPosZ->TransThisTextToThisInt();
    posData.pos.b.x2 = ui->releaseProductPosX2->TransThisTextToThisInt();
    posData.pos.b.y2 = ui->releaseProductPosY2->TransThisTextToThisInt();
    posData.fixtureConfis = releaseProductCFConfigs_;
    stData_->releaseProductPosList[toModifyIndex] = posData;
    selected[0]->setText(PosDataToString(posData));
}

void ICSimpleTeachPage::on_deleteProductPos_clicked()
{
    QList<QListWidgetItem*> selected = ui->releasePosView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->releasePosView->row(selected.at(0));
    stData_->releaseProductPosList.removeAt(toModifyIndex);
    delete ui->releasePosView->takeItem(toModifyIndex);

    DelPosHelper(toModifyIndex, ui->releaseProductSpeedGroup, releaseProductSpeedUI, tr("Rel Product"));

}


void ICSimpleTeachPage::on_addOutletPos_clicked()
{
    ReleasePosData posData;
    posData.pos.b.x1 = ui->releaseOutletPosX1->TransThisTextToThisInt();
    posData.pos.b.y1 = ui->releaseOutletPosY1->TransThisTextToThisInt();
    posData.pos.b.z = ui->releaseOutletPosZ->TransThisTextToThisInt();
    posData.pos.b.x2 = ui->releaseOutletPosX2->TransThisTextToThisInt();
    posData.pos.b.y2 = ui->releaseOutletPosY2->TransThisTextToThisInt();
    posData.fixtureConfis = (releaseOutletCFConfigs_);
    stData_->releaseOutletPosList.append(posData);
    ui->releaseOutletView->addItem(PosDataToString(posData));

    AddPosHelper(ui->releaseOutletSpeedGroup, releaseOutletSpeedUI, tr("Rel Outlet"), posData.pos.b.x1S);
}

void ICSimpleTeachPage::on_modifyOutletPos_clicked()
{
    QList<QListWidgetItem*> selected = ui->releaseOutletView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->releaseOutletView->row(selected.at(0));
    ReleasePosData posData;
    posData.pos.b.x1 = ui->releaseOutletPosX1->TransThisTextToThisInt();
    posData.pos.b.y1 = ui->releaseOutletPosY1->TransThisTextToThisInt();
    posData.pos.b.z = ui->releaseOutletPosZ->TransThisTextToThisInt();
    posData.pos.b.x2 = ui->releaseOutletPosX2->TransThisTextToThisInt();
    posData.pos.b.y2 = ui->releaseOutletPosY2->TransThisTextToThisInt();
    posData.fixtureConfis = (releaseOutletCFConfigs_);
    stData_->releaseOutletPosList[toModifyIndex] = posData;
    selected[0]->setText(PosDataToString(posData));

}

void ICSimpleTeachPage::on_deleteOutletPos_clicked()
{
    QList<QListWidgetItem*> selected = ui->releaseOutletView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->releaseOutletView->row(selected.at(0));
    stData_->releaseOutletPosList.removeAt(toModifyIndex);
    delete ui->releaseOutletView->takeItem(toModifyIndex);

    DelPosHelper(toModifyIndex, ui->releaseOutletSpeedGroup, releaseOutletSpeedUI, tr("Rel Outlet"));
}

void ICSimpleTeachPage::on_addCut_clicked()
{
    ReleasePosData posData;
    posData.pos.b.x1 = ui->cutOutletPosX1->TransThisTextToThisInt();
    posData.pos.b.y1 = ui->cutOutletPosY1->TransThisTextToThisInt();
    posData.pos.b.z = ui->cutOutletPosZ->TransThisTextToThisInt();
    posData.fixtureConfis = cutOutletCFConfigs_;
    stData_->cutOutletPosList.append(posData);
    ui->cutPosView->addItem(PosDataToString(posData, true));

    AddPosHelper(ui->cutOutletSpeedGroup, cutOutletSpeedUI, tr("Cut Pos"), posData.pos.b.x1S);
}

void ICSimpleTeachPage::on_modifyCut_clicked()
{
    QList<QListWidgetItem*> selected = ui->cutPosView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->cutPosView->row(selected.at(0));
    ReleasePosData posData;
    posData.pos.b.x1 = ui->cutOutletPosX1->TransThisTextToThisInt();
    posData.pos.b.y1 = ui->cutOutletPosY1->TransThisTextToThisInt();
    posData.pos.b.z = ui->cutOutletPosZ->TransThisTextToThisInt();
    posData.fixtureConfis = cutOutletCFConfigs_;
    stData_->cutOutletPosList[toModifyIndex] = posData;
    selected[0]->setText(PosDataToString(posData, true));
}

void ICSimpleTeachPage::on_deleteCut_clicked()
{
    QList<QListWidgetItem*> selected = ui->cutPosView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->cutPosView->row(selected.at(0));
    stData_->cutOutletPosList.removeAt(toModifyIndex);
    delete ui->cutPosView->takeItem(toModifyIndex);

    DelPosHelper(toModifyIndex, ui->cutOutletSpeedGroup, cutOutletSpeedUI, tr("Cut Pos"));
}




void ICSimpleTeachPage::on_getProductFSel_clicked()
{
    fixtureSel_->ShowEditor(stData_->getProductPos.fixtureConfis);
    stData_->getProductPos.fixtureConfis = fixtureSel_->GetConfigs();
    ui->getProductFInfo->setText(fixtureSel_->SelectedNames(stData_->getProductPos.fixtureConfis).join(","));
}

void ICSimpleTeachPage::on_getOutletFSel_clicked()
{
    fixtureSel_->ShowEditor(stData_->getOutletPos.fixtureConfis);
    stData_->getOutletPos.fixtureConfis = fixtureSel_->GetConfigs();
    ui->getOutletFInfo->setText(fixtureSel_->SelectedNames(stData_->getOutletPos.fixtureConfis).join(","));
}

void ICSimpleTeachPage::on_releaseProductFSel_clicked()
{
    fixtureSel_->ShowEditor(releaseProductCFConfigs_, true);
    releaseProductCFConfigs_ = fixtureSel_->GetConfigs();
    ui->releaseProductCFInfo->setText(fixtureSel_->SelectedNames(releaseProductCFConfigs_).join(","));
}

void ICSimpleTeachPage::on_releaseOutletFSel_clicked()
{
    fixtureSel_->ShowEditor(releaseOutletCFConfigs_, true);
    releaseOutletCFConfigs_ = fixtureSel_->GetConfigs();
    ui->releaseOutletCFInfo->setText(fixtureSel_->SelectedNames(releaseOutletCFConfigs_).join(","));
}

void ICSimpleTeachPage::on_cutFSel_clicked()
{
    fixtureSel_->ShowEditor(cutOutletCFConfigs_, true);
    cutOutletCFConfigs_ = fixtureSel_->GetConfigs();
    ui->cutFInfo->setText(fixtureSel_->SelectedNames(cutOutletCFConfigs_).join(","));
}

void ICSimpleTeachPage::on_cutOutletEn_toggled(bool checked)
{
    SetCutOutletEnabled(checked);
}