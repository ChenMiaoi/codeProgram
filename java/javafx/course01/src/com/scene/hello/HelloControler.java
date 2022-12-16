package com.scene.hello;

import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class HelloControler {
    @FXML private Label label;
    @FXML
    protected void onHelloPick() {
        label.setText("哎哟！");
    }
}
