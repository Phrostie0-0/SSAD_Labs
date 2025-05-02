#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Memento: holds editor state
class Memento {
public:
    Memento(const string& state)
            : state(state) {}

    string getState() const {
        return state;
    }

private:
    string state;
};

// Originator: the text editor
class TextEditor {
public:
    TextEditor() = default;

    void appendText(const string& newText) {
        text += newText;
    }

    string getText() const {
        return text;
    }

    // Capture current state
    Memento save() const {
        return Memento(text);
    }

    void restore(const Memento& memento) {
        text = memento.getState();
    }

private:
    string text;
};

// Caretaker: manages undo/redo stacks
class UndoRedoManager {
public:
    UndoRedoManager() = default;

    void saveState(TextEditor& editor) {
        undoStack.push(editor.save());
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    void undo(TextEditor& editor) {
        if (undoStack.empty()) {
            cout << "[Undo] Nothing to undo" << endl;
            return;
        }
        redoStack.push(editor.save());
        undoStack.pop();
        Memento m = undoStack.top();
        editor.restore(m);
    }

    void redo(TextEditor& editor) {
        if (redoStack.empty()) {
            cout << "[Redo] Nothing to redo" << endl;
            return;
        }
        undoStack.push(editor.save());
        Memento m = redoStack.top();
        redoStack.pop();
        editor.restore(m);
    }

private:
    stack<Memento> undoStack;
    stack<Memento> redoStack;
};

int main() {
    TextEditor editor;
    UndoRedoManager undoRedoManager;

    // Initial text
    cout << "Initial text: " << editor.getText() << endl;

    // Append some text and save state
    editor.appendText("Hello");
    undoRedoManager.saveState(editor);
    cout << "After appending 'Hello': " << editor.getText() << endl;

    // Append more text and save state
    editor.appendText(" World");
    undoRedoManager.saveState(editor);
    cout << "After appending ' World': " << editor.getText() << endl;

    // Undo and show state
    undoRedoManager.undo(editor);
    cout << "After undoing: " << editor.getText() << endl;

    // Redo and show state
    undoRedoManager.redo(editor);
    cout << "After redoing: " << editor.getText() << endl;

    return 0;
}