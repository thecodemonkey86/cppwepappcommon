#include "html.h"

HtmlSelect Html::select() {
    return HtmlSelect();
}

HtmlSelectOption Html::option(const QString &value, const QString &display) {
    return HtmlSelectOption(value,display);
}
