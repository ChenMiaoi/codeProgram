function [m, s] = FindSum(input)
    %FINDSUM 此处显示有关此函数的摘要
    %   此处显示详细说明
    s = 0; m = 0;
    while (s <= input)
        m = m + 1;
        s = s + m;
    end
end

