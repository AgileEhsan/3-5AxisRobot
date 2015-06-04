#ifndef ICHCCONDITIONPAGE_H
#define ICHCCONDITIONPAGE_H

#include <QFrame>
#include "icinstructioneditorbase.h"
#include <QButtonGroup>

namespace Ui {
    class ICHCConditionPage;
}

class ICHCConditionPage : public ICInstructionEditorBase
{
    Q_OBJECT

public:
    explicit ICHCConditionPage(QWidget *parent = 0);
    ~ICHCConditionPage();

    void ResetFlagSel(const QStringList& selList);

protected:
    void changeEvent(QEvent *);
    void SyncStatusImpl(const QList<ICMoldItem> &items);
    QList<ICMoldItem> CreateCommandImpl() const;

private:
    Ui::ICHCConditionPage *ui;
    QButtonGroup* buttonGroup;
    void InitCheckPointBox();

private slots:
    void BoxClicked();
    void on_productCountBox_toggled(bool checked);
};

#endif // ICHCCONDITIONPAGE_H
