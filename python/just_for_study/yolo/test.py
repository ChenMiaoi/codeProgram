import torch
import inspect
from collections import defaultdict
import pandas as pd
from torch.utils import benchmark

print(torch.__version__)
print(torch.version.cuda)
print(torch.cuda.get_device_name())

pd.options.display.precision = 3

def var_dict(*args):
    callers_local_vars = inspect.currentframe().f_back.f_locals.items()
    return dict([(name, val) for name, val in callers_local_vars if val is arg][0]
                for arg in args)

def walltime(stmt, arg_dict, duration = 3):
    return benchmark.Timer(stmt = stmt, globals = arg_dict).blocked_autorange(
        min_run_time = duration
    ).mean

matmul_tflops = defaultdict(lambda: {})
for n in [128, 512, 2048, 8192]:
    for dtype in (torch.float32, torch.float16):
        a = torch.randn(n, n, dtype = dtype).cuda()
        b = torch.randn(n, n, dtype = dtype).cuda()
        t = walltime('a @ b', var_dict(a, b))
        matmul_tflops[f'n={n}'][dtype] = 2 * n ** 3 / t / 1e12
        del a, b

print(pd.DataFrame(matmul_tflops))

vector = defaultdict(lambda: {})
for n in [1024 * 64, 1024 * 256, 1024 * 1024, 1024 * 1024 * 4]:
    a = torch.randn(n).cuda()
    t = walltime('a * 1.2', var_dict(a))
    vector[n]['TFLOPS'] = n / t / 1e12
    vector[n]['GB/s'] = 8 * n / t / 1e9

print(pd.DataFrame(vector))
