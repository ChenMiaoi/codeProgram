function boat(status, move)
    global ii;
    [flag, choice] = checkAllFail(status); % 如果五种决策都不可以, flag == 1
    if flag == 1
        [status, move] = allFail(status, move); % 删除现有状态
    end
    temp_s = status;
    temp_m = move;
    for i = 1 : length(choice)
        status = temp_s;
        if sum(status(end, : ) == [0 0 1]) == 3
            ii = ii + 1;
            if mod(ii, 2) == 0 % 奇数和对应的偶数会成为一种相同的方案，因此只需要取奇数次或偶数次
                fprintf("方案 (%d) \n", ii / 2);
                Print(status, move);
            end
        else
            new_status = operation(status(end, :), decision(choice(i)));
            new_move = decision(choice(i));
            boat([status, new_status], [move, new_move]);
        end
    end
end

