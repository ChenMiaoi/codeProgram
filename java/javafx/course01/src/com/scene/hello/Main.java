package com.scene.hello;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class Main extends Application {
    private class MyEventHandler implements EventHandler<ActionEvent> {
        @Override
        public void handle(ActionEvent event) {
            System.out.println("哎哟!");
        }
    }
    @Override
    public void start(Stage stage) throws Exception {
//        Label label = new Label("Hello World"); // 标签 -> 文本
//        BorderPane pane = new BorderPane();
//        pane.setCenter(label);
//        Button button = new Button("Pick Me!");
//        pane.setCenter(button);
//        // MyEventHandler myEventHandler = new MyEventHandler();
//        button.setOnAction(new EventHandler<ActionEvent>() {
//            @Override
//            public void handle(ActionEvent arg) {
//                System.out.println("哎呀！");
//            }
//        });
//        Scene scene = new Scene(fxmlLoader.load(), 640, 480);
//        stage.setScene(scene);
//        stage.setTitle("New Title");
//        stage.show();
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 640, 480);
        stage.setScene(scene);
        stage.setTitle("New Title");
        stage.show();
    }

    public static void main(String[] args) {
        Application.launch(args);
        // launch方法会自动调用start方法，然后通过stage来构建窗口, 而且launch方法可以直接被调用，不需要声明Application
    }
}
