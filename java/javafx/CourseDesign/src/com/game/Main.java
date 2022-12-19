package com.game;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class Main extends Application {
    @Override
    public void start(Stage stage) {
        GameWindow gameWindow = new GameWindow();

        Scene scene = new Scene(gameWindow, 640, 480);
        stage.setScene(scene);
        stage.setTitle("The Maze Game");
        stage.show();
    }
    public static void main(String[] args)  {
        Application.launch(args);
    }
}