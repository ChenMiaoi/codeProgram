function PlotTest(x, color)
    %PLOTTEST 此处显示有关此函数的摘要
    %color 控制颜色的参数,输入RGB三元组
    y = sin(tan(x)) - tan(sin(x));
    plot(x, y, Color=color)
end

