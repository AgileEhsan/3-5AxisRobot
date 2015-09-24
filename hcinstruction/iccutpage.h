#ifndef ICCUTPAGE_H
#define ICCUTPAGE_H

#include <QMap>
#include <QSignalMapper>
#include "icinstructioneditorbase.h"
#include "iclineeditwithvirtualnumerickeypad.h"

namespace Ui {
    class ICCutPage;
}

class QAbstractButton;

class ICCutPage : public ICInstructionEditorBase
{
    Q_OBJECT

public:
    explicit ICCutPage(QWidget *parent = 0);
    ~ICCutPage();

signals:
    void GoToAxis();
    void GoToFixture();

protected:
    void changeEvent(QEvent *);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    void SyncStatusImpl(const QList<ICMoldItem> &items);
    QList<ICMoldItem> CreateCommandImpl() const;

private Q_SLOTS:
    void StatusRefreshed();
    void CommandButtonClicked(QWidget* widget);

    void on_goToAxis_clicked();

    void on_goToFixture_clicked();

private:
    Ui::ICCutPage *ui;
private:
    QVector<QAbstractButton*> settingButtons_;
//    QVector<ICLineEditWithVirtualNumericKeypad*> delayEdits_;
    QMap<QAbstractButton*, uint> buttonToClip_;
    QMap<uint, uint> onClipToOffClip_;
    QMap<uint, uint> offClipToOnClip_;
    QStringList ioNames_;
    QMap<QAbstractButton*, QPair<int, int> > commandKeyMap_;
    QSignalMapper buttonSignalMapper_;
    QPixmap onPixmap_;
    QPixmap offPixmap_;

};

#endif // ICCUTPAGE_H
