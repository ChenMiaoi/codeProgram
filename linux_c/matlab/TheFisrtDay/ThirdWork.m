function ThirdWork()
    x = 0 : 0.2 : 10;
    y = 0.25 * x + 20 * sin(x);
    % 5阶多项式拟合
    p5=polyfit(x,y,5);
    y5=polyval(p5,x);
    % 8阶多项式拟合
    p8=polyfit(x,y,8);
    y8=polyval(p8,x);
    % 51阶多项式拟合
    p51=polyfit(x,y,51);
    y51=polyval(p51,x);

    figure
    plot(x,y,'ro');
    hold on;
    plot(x,y5,'b--');
    plot(x,y8,'b:');
    plot(x,y51,'r-.');
    xlabel('x');
    ylabel('y');
    legend('原始数据','5阶多项式','8阶多项式','51阶多项式');

end

