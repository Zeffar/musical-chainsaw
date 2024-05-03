import matplotlib.pyplot as plt
def process_data():
    file = open("../benchmark.txt", "r")
    file_content = file.readlines()

    data = {}
    bench_list = ["SkewBinomial", "StrictFibonacci", "BinaryHeap", "2-3 Heap"]
    bench_trials = ["insertion", "deletion", "merging"]
    idx = 0
    tidx = 0
    for line in file_content:
        algorithm_name = bench_list[idx]
        idx += 1
        idx %= 4
        trial = bench_trials[int(tidx/15)]
        tidx+=1
        if algorithm_name not in data:
            data[algorithm_name] = {}
        if trial not in data[algorithm_name]:
            data[algorithm_name][trial] = []
        data[algorithm_name][trial].append(float(line))
    return data


def draw(input_size, execution_times_1, execution_times_2, sort_label, label1, label2):
    plt.clf()
    plt.plot(input_size, execution_times_1, marker='o', label=label1, color='purple')
    plt.plot(input_size, execution_times_2, marker='o', label=label2, color='red')

    plt.title(f'{sort_label} Performance')
    plt.xlabel('Size of Array (N)')
    plt.ylabel('Execution Time (seconds)')
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'{sort_label}.png')
    plt.show()

array_sizes = [1000, 10000, 100000, 1000000, 10000000]
data = process_data()
for key in data:
    if key != "BinaryHeap":
        print(key, data[key])
        draw(array_sizes, data[key]["insertion"], data["BinaryHeap"]["insertion"], f"Insertion on {key}", key, "BinaryHeap")
        draw(array_sizes, data[key]["deletion"], data["BinaryHeap"]["deletion"], f"deletion on {key}", key, "BinaryHeap")
        draw(array_sizes, data[key]["merging"], data["BinaryHeap"]["merging"], f"merging on {key}", key, "BinaryHeap")