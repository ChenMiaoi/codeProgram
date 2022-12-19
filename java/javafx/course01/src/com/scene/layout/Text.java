package com.scene.layout;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.stage.Stage;


public class Text extends Application {
    HBox hBox = new HBox();
    TextArea textField = new TextArea();
    Button button1 = new Button("添加");
    Button button2 = new Button("清空");
    TextArea textArea = new TextArea();
    @Override
    public void start(Stage stage) {
        hBox.getChildren().addAll(textField, button1, button2);
        HBox.setHgrow(textField, Priority.ALWAYS);
        hBox.setPadding(new Insets(10));
        hBox.setPrefHeight(20);

        BorderPane borderPane = new BorderPane();
        borderPane.setTop(hBox);
        borderPane.setCenter(textArea);

        button1.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                onAdd();
            }
        });

        button2.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                onClear();
            }
        });

        Scene scene = new Scene(borderPane, 640, 480);
        stage.setScene(scene);
        stage.show();
    }

    public void onAdd() {
        String str = textField.getText();
        textArea.appendText(str);
    }

    public void onClear() {
        textField.clear();
        textArea.clear();
    }
    public static void main(String[] args) {
        Application.launch(args);
    }
}
