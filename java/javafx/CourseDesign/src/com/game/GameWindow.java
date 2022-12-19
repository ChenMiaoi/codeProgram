package com.game;

import javafx.scene.control.MenuBar;
import javafx.scene.layout.BorderPane;

public class GameWindow extends BorderPane {
    GameHBox gameHBox = new GameHBox();
    public GameWindow() {
        super();
        setTop(gameHBox);
    }
}
