import QtQuick 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12


TextFieldWithTitle {
    readonly property int max_length: 50

    field.validator: RegExpValidator {
        regExp: /[a-zA-Z0-9 \t]{25,50}/
    }
    field.onTextChanged: {
        if(field.text.indexOf(' ') !== -1 || field.text.indexOf('\t') !== -1) {
            field.text = field.text.replace(/[ \t]/, '')
        }
        if(field.text.length > max_length) {
            console.log("too long! ", field.text.length)
            field.text = field.text.substring(0, max_length)
        }
    }
}
