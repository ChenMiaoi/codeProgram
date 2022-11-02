function [output] = SecondWork(input)
    %SECONDWORK 此处显示有关此函数的摘要
    %   此处显示详细说明
    if input == 0
        output =  1;
    elseif input == 1
        output =  1;
    else
        output =  input * SecondWork(input - 1);
    end
end

