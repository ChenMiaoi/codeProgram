package com.scene.layout;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.stage.Stage;

public class Main extends Application {
    @Override
    public void start(Stage stage) {
        // 边缘布局 -> 上下左右中
        BorderPane borderPane = new BorderPane();
        // borderPane.setCenter(new Button("中"));
        // borderPane.setTop(new Button("上"));
        // borderPane.setBottom(new Button("下"));
        // borderPane.setLeft(new Button("左"));
        // borderPane.setRight(new Button("右"));

        // 水平布局 -> HBox
        HBox hBox = new HBox();
        // hBox.getChildren().add(new TextField()); // 文本输入框
        // hBox.getChildren().add(new Button("选择文件"));
        // hBox.getChildren().add(new Button("上传文件"));
        borderPane.setTop(hBox);
        TextField textField = new TextField();
        hBox.getChildren().addAll(textField, new Button("选择文件"), new Button("上传文件"));
        HBox.setHgrow(textField, Priority.ALWAYS); // 使文本框水平增长占满空间
        hBox.setAlignment(Pos.CENTER); // 设置水平居中
        hBox.setPadding(new Insets(10)); // 设置居中垂直间隔距离

        Scene scene = new Scene(borderPane, 640, 480);
        stage.setScene(scene);
        stage.show();
    }
    public static void main(String[] args) {
        Application.launch(args);
    }
}
