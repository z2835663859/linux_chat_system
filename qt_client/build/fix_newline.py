with open("qt_client/src/ui/main_window.cpp", "r") as f:
    text = f.read()
text = text.replace('messaging app.\nSelect', 'messaging app.\\nSelect')
with open("qt_client/src/ui/main_window.cpp", "w") as f:
    f.write(text)
