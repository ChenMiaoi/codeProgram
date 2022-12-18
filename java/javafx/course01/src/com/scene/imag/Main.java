package com.scene.imag;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

import java.io.File;

public class Main extends Application {
    @Override
    public void start(Stage stage) {
        BorderPane borderPane = new BorderPane();

        // Imag or ImagView
        String url_img = new File("/home/zack/图片/QQ_Image_1670770010564.jpg").toURI().toString();
        Image image = new Image(url_img); // url， 如果是本地图片，那么要在前面家一个file:
        ImageView imageView = new ImageView();
        imageView.setImage(image);
        imageView.setFitHeight(480);
        imageView.setFitWidth(640);
        borderPane.setCenter(imageView);
        Scene scene = new Scene(borderPane, 640, 480);
        stage.setScene(scene);
        stage.show();
    }
    public static void main(String[] args) {
        Application.launch(args);
    }
}
