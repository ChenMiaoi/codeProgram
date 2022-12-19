package com.scene.layout;

import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;

public class MyImagePane extends Pane {
    @Override
    protected void layoutChildren() {
        if (getChildren().size() == 0)
            return;
        double w = getWidth();
        double h = getHeight();

        ImageView imageView = (ImageView) getChildren().get(0);
        imageView.resizeRelocate(0, 0, w, h);
        imageView.setFitWidth(w);
        imageView.setFitHeight(h);
        imageView.setPreserveRatio(true);
    }
}
