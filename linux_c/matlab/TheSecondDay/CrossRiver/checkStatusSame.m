function [flag] = checkStatusSame(now_status, pre_status)
    % checkStatusSame 检查当前状态集是否和之前状态集重复，避免循环
    flag = 0;
    for i = 1 : size(pre_status, 1)
        if sum(now_status == pre_status(i, :)) == 3
            flag = 1;
        end
    end
end

