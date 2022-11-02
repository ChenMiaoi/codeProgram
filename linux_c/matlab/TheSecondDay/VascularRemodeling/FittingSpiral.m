function FittingSpiral(result)
    % FittingSpiral 画出立体重构后的血管彩图
    
    format long;
    center = result; % 读取中心坐标
    x = center(:, 1); % x轴
    y = center(:, 2); % y轴
    z = center(:, 3); % z轴
    x_polyfit = polyfit(z, x, 7); % 在zx平面上拟合7次能够达到最优值
    x1 = polyval(x_polyfit, z); % 取拟合后在Z的点
    y_polyfit = polyfit(z, y, 7); % 在zy平面上拟合7次能够达到最优值
    y1 = polyval(y_polyfit, z); % 取拟合后在Z的点

    central_axis = zeros(100, 3); % 存储中轴线坐标
    % 存入坐标集
    central_axis(:, 1) = x1;
    central_axis(:, 2) = y1;
    central_axis(:, 3) = z;
    
    t = linspace(0, pi, 25); % 存储平均为pi的25份
    p = linspace(0, 2 * pi, 25); % 存储平均为2pi的25份
    [theta, phi] = meshgrid(t, p); % 存储角度
    % meshgrid基于向量 x 和 y 中包含的坐标返回二维网格坐标X, Y
    for i = 1 : 100
        % x，y，z特定的算法取值
        x=29.4166 * sin(theta) .* sin(phi) + central_axis(i,1);
        y=29.4166 * sin(theta) .* cos(phi) + central_axis(i,2);
        z=29.4166 * cos(theta) + central_axis(i,3);
        
        surf(x, y, z); % 使图像变为彩色
        axis([-200, 200, -50, 200, -50, 150]);
        hold on
    end
    hold off;
    xlabel('X轴'); 
    ylabel('Y轴'); 
    zlabel('Z轴');  
    title('血管拟合后还原图');      
end

