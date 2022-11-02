function [p, s] = PolyfitTest(x, y, n)
    %PolyfitTest 使用polyfit(x, y, n)来进行拟合操作
    %            再使用polyvar(p, x)来绘制拟合曲线
    %params{
        %   x,y 为数据点集, x必须是单调的
        %   n 为多项式阶数
    % }
    %return{
        %   p 为幂次从高到低的多项式系数向量
        %   s 用于生成预测值的误差估计
        %   ret 得到的拟合曲线y
    % }

    figure
    plot(x, y, '*');
    hold on;
    [p, s] = polyfit(x, y, n);
    x1 = 0.5 : 0.05 : 3.0;
    y1 = polyval(p, x1);
    plot(x, y, '*r', x1, y1, '-b');
    disp(p);
end

