function Spiral(x, y, z)
    % Spiral 绘制三维螺旋线

    subplot(2, 2, 1);
    plot3(x, y, z, 'red', 'LineWidth', 2);
    xlabel("X轴");
    ylabel("Y轴");
    zlabel("Z轴");
    title("中轴线拟合后的立体图形")
    subplot(2, 2, 2);
    z_shape = size(z);
    z_shape = zeros(z_shape);
    plot3(x, y, z_shape, 'red', 'LineWidth', 2);
    xlabel("X轴");
    ylabel("Y轴");
    zlabel("Z轴");
    title("中轴线X - Y平面图")
    subplot(2, 2, 3);
    y_shape = size(y);
    y_shape = zeros(y_shape);
    plot3(x, y_shape, z, 'red', 'LineWidth', 2);
    xlabel("X轴");
    ylabel("Y轴");
    zlabel("Z轴");
    title("中轴线X - Z平面图")
    subplot(2, 2, 4)
    x_shape = size(x);
    x_shape = zeros(x_shape);
    plot3(x_shape, y, z, 'red', 'LineWidth', 2);
    xlabel("X轴");
    ylabel("Y轴");
    zlabel("Z轴");
    title("中轴线Z - Y平面图")
end

