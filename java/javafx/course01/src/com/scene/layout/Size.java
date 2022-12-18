package com.scene.layout;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Control;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.stage.Stage;

public class Size extends Application {
    @Override
    public void start(Stage stage) {
        HBox hBox = new HBox();
        Button button1 = new Button("中国");
        Button button2 = new Button("China");
        Button button3 = new Button("中华人民共和国");

        // 对于HBox的控件
        // 修改Pref才会对水平方向产生影响
        // 修改Max才会对垂直方向产生影响
        button1.setMinWidth(10); // 最小宽度
        button2.setPrefWidth(100); // 最佳宽度
        button3.setMaxWidth(400); // 最大宽度

        button3.setPrefWidth(Control.USE_COMPUTED_SIZE);
        button3.setMaxHeight(Control.USE_PREF_SIZE);

        /*
        * Control.USE_COMPUTED_SIZE 会自动获取图片的大小
        * Control.USE_PREF_SIZE     使用最适合图片的大小
        * Double.MAX_VALUE          理论的最大值
        * */

        hBox.getChildren().addAll(button1, button2, button3);

        Scene scene = new Scene(hBox, 640, 480);
        stage.setScene(scene);
        stage.show();
    }
    public static void main(String[] args) {
        Application.launch(args);
    }
}
