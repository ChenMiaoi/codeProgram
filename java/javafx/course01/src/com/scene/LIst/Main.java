package com.scene.LIst;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Scene;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.sql.Struct;

public class Main extends Application {
    static class Student {
        private int num;
        private String name;

        public Student(int num, String name) {
            this.num = num;
            this.name = name;
        }
    }
    ListView<Student> listView = new ListView<Student>();
    ObservableList<Student> listBase = FXCollections.observableArrayList();
    public void start(Stage stage) {
        listBase.add(new Student(1, "HH"));
        listBase.add(new Student(2, "asd"));

        listView.setItems(listBase);

        listView.setCellFactory(new Callback<ListView<Student>, ListCell<Student>>() {
            @Override
            public ListCell<Student> call(ListView<Student> param) {
                return new MyListCell();
            }
        });

        BorderPane borderPane = new BorderPane();
        borderPane.setCenter(listView);
        Scene scene = new Scene(borderPane, 640, 480);
        stage.setScene(scene);
        stage.show();
    }

    class MyListCell extends ListCell<Student> {
        @Override
        public void updateItem(Student item, boolean empty) {
            super.updateItem(item, empty);
            if (item != null)
                this.setText(item.num + item.name);
        }
    }
    public static void main(String[] args) {
        Application.launch(args);
    }
}
