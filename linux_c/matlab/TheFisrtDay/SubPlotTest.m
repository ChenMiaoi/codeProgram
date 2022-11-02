function SubPlotTest(x)
%params{
    %   SubPlotTest 绘制子图
    %   x x轴坐标系
    %   y y轴坐标系
    %   varargin plot函数的Color参数，使用[R, G, B]三元组，范围为0~1, 必须为四个参数
    %   stairs 梯阶图
    %   stem 绘制离散序列数据
    %   bar 绘制扇形图
    %   semilogx 对半数图(x轴有刻度)
%}
    %if length(varargin) ~= 4
    %    error("The color params is not 4!");
    %end
    y = sin(x);
    subplot(2, 2, 1);
    stairs(x, y);
    subplot(2, 2, 2);
    stem(x, y);
    subplot(2, 2, 3);
    bar(x, y);
    subplot(2, 2, 4);
    semilogx(y);
end

