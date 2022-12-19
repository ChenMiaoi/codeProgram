package com.game;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.SeparatorMenuItem;
import javafx.scene.layout.HBox;

public class GameHBox extends HBox {
    MenuBar menuBar = new MenuBar();
    public GameHBox() {
        super();
        Menu menuGame = new Menu("游戏");
        Menu menuHelp = new Menu("帮助");

        MenuItem menuItemNewGame = new MenuItem("新游戏");
        MenuItem menuItemExit = new MenuItem("退出");
        MenuItem menuItemDoc = new MenuItem("使用说明");
        MenuItem menuItemVersion = new MenuItem("版本");

        menuGame.getItems().addAll(menuItemNewGame, menuItemExit);
        menuHelp.getItems().addAll(menuItemDoc, menuItemVersion);
        menuBar.getMenus().addAll(menuGame, menuHelp);

        menuItemNewGame.setOnAction((ActionEvent e) -> {
            System.out.println("TODO New Game");
        });
        menuItemExit.setOnAction((ActionEvent e) -> {
            Platform.exit();
        });
        menuItemDoc.setOnAction((ActionEvent e) -> {
            System.out.println("TODO Show Doc");
        });
        menuItemVersion.setOnAction((ActionEvent e) -> {
            System.out.println("TODO Show Version");
        });
        getChildren().addAll(menuBar);
    }
}
