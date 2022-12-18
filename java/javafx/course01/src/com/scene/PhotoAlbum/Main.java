package com.scene.PhotoAlbum;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class Main extends Application {
    String[] imageUrls = { // 注意，此处的路径如果使用相对路径，那么最好从源开始
            "com/scene/PhotoAlbum/res/img1.jpeg",
            "com/scene/PhotoAlbum/res/img2.jpeg",
            "com/scene/PhotoAlbum/res/img3.jpeg"
    };

    Image[] images = new Image[3];
    ImageView imageViews = new ImageView();
    int curentPicture = 0;
    @Override
    public void start(Stage stage) {
        BorderPane borderPane = new BorderPane();
        Button button = new Button("Next");
        // 加载图片
        for (int i = 0; i < images.length; i++) {
            images[i] = new Image(imageUrls[i]);
        }

        button.setOnAction(new EventHandler<ActionEvent>() { // 点击播放下一张
            @Override
            public void handle(ActionEvent event) {
                showNext();
            }
        });

        // 设置图片自适应窗口 -> 保持比例
        imageViews.setPreserveRatio(true); // 保持比例的API
        imageViews.setFitWidth(640);
        imageViews.setFitHeight(480);

        borderPane.setTop(button); // 上面显示图片
        borderPane.setCenter(imageViews); // 中间显示图片

        Scene scene = new Scene(borderPane, 640, 480);
        stage.setScene(scene);
        stage.setTitle("Photo Album");
        stage.show();

        // 在这里不加showNext没有什么问题，但是会在刚开始启动程序都时候产生一个小BUG -> 第一张图片是空，但是不会影响后续
        showNext();
    }

    private void showNext() {
        if (curentPicture > 2)
            curentPicture %= 3;
        imageViews.setImage(images[curentPicture]);
        curentPicture++;
    }
    public static void main(String[] args) {
        Application.launch(args);
    }
}
