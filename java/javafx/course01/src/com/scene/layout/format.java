package com.scene.layout;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Control;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.stage.Stage;

public class format extends Application {
    TextField textField = new TextField();
    Button button1 = new Button("选择文件");
    Button button2 = new Button("上传文件");
    @Override
    public void start(Stage stage) {
        /*
        * 填充、间距和对齐
        * Padding：填充子控件与父级之间都边距
        * Spacing：各个子控件的间距
        * Alignment：对齐，靠左、靠右...
        * */

        HBox hBox = new MyHBox();
        hBox.getChildren().addAll(textField, button1, button2);

        hBox.setPadding(new Insets(10)); // Insets的参数分别是：上右下左
        hBox.setSpacing(10);
        hBox.setAlignment(Pos.CENTER); // 设置了居中对其，其中水平方向和垂直方向都会居中
        HBox.setHgrow(textField, Priority.ALWAYS); // 水平自动增长 -> 优先级更高

        /*
        * 精确布局
        * 文本框：固定300px
        * button1：剩余空间的50%
        * button2：剩余空间的50%
        * */

        Scene scene = new Scene(hBox, 640, 40);
        stage.setScene(scene);
        stage.show();
    }

    class MyHBox extends HBox {
        @Override
        protected void layoutChildren() {
            // 如果自己实现布局，那么就不需要调用父类
            // super.layoutChildren();

            double width = getWidth();
            double height = getHeight();

            double text = 300;
            double button_1 = prefWidth(width - 300);
            double button_2 = width - text - button_1;

            // 定位
            double x = 0;
            textField.resizeRelocate(x, 0, text, height);
            x += text;
            button1.resizeRelocate(x, 0, button_1, height);
            x += button_1;
            button2.resizeRelocate(x, 0, button_2, height);
        }
    }
    public static void main(String[] args) {
        Application.launch(args);
    }
}
