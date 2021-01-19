// This js file is unused for now. Using Component {} instead
// Until this is needed
var parent_var
var lang_var
var file_var
var iters_var
var limit_var
var component

function create_code(parent_var_, lang_var_, file_var_, iters_var_, limit_var_) {
    parent_var = parent_var_
    lang_var = lang_var_
    file_var = file_var_
    iters_var = iters_var_
    limit_var = limit_var_
    print ("Variables set")

    component = Qt.createComponent("qrc:/components/CodeButton.qml");
    if (component.status === Component.Ready) {
        finish_code_creation();
    } else {
        component.statusChanged.connect(finish_code_creation);
    }
}


function finish_code_creation() {
    if (component.status === Component.Ready) {
        var code = component.createObject(
                    parent_var,
                    {
                        language: lang_var, file: file_var, iters: iters_var,
                        limit: limit_var
                    });

        if (code === null) {
            // Error Handling
            console.log("Error creating QML CodeButton object");
        } else {
            // Append to the model
            parent_var.append(code)
        }

    } else if (component.status === Component.Error) {
        // Error Handling
        console.log("Error loading QML CodeButton: ",
                    component.errorString());
    }
}
