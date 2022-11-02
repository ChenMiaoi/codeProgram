function [flag, choice] = checkAllFail(status)
    %checkAllFail 检验是否五种决策都不可行，如果可行，返回可行的决策序号
    flag = 0;
    dec_sum = 0;
    last_status = status(end, : ); % 通过这个获取到第一次前往的-1
    dir = last_status(end); % Sk+1 = Sk + ((-1)^k)Dk
    choice = [];
    for i = 1 : 5
        % 对每一步的新状态进行检查
        move = [decision(i), 0]; % 获得的决策
        next_status = status(end, : ) + dir * move; % Sk+1 = Sk + ((-1)^k)Dk
        next_status(end) = next_status(end) * (-1); % 前往之后就应该返航，返航后又前往，是一个控制因子
        is_state_set = abs(checkStatusSet(next_status) - 1); % 检查下一状态是否在合法状态集中
        is_state_same = checkStatusSame(next_status, status);

        if is_state_same || is_state_set
            dec_sum = dec_sum + 1;
        else
            choice(end + 1) = i;
        end
    end
    if dec_sum == 5
        flag = 1; % 如果五种操作均不可以，那么判断状态不可接受，回到上一状态
    end 
end

