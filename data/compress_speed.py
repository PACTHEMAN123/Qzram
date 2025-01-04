def calculate_avg_time(file_path):
    with open(file_path, 'r') as file:
        # 读取并按空行分割内容
        sections = file.read().split('\n\n')

    for idx, section in enumerate(sections, start=1):
        total_read_time = 0
        total_write_time = 0
        read_operations = 0
        write_operations = 0

        for line in section.splitlines():
            parts = line.split()
            if len(parts) < 8:
                continue  # 忽略不完整的行

            read_ops = int(parts[0])  # 读操作数量
            read_time = float(parts[3])  # 读操作总用时（ms）
            write_ops = int(parts[4])  # 写操作数量
            write_time = float(parts[7])  # 写操作总用时（ms）

            if read_ops > 0:
                total_read_time += read_time / read_ops  # 计算每次读操作的平均时间
                read_operations += 1
            if write_ops > 0:
                total_write_time += write_time / write_ops  # 计算每次写操作的平均时间
                write_operations += 1

        if idx == 1:
            avg_read_time = total_read_time / read_operations
            print(f"qzram的平均一次读: {avg_read_time:.5f} ms")
            avg_write_time = total_write_time / write_operations
            print(f"qzram的平均写用时: {avg_write_time:.5f} ms")

        if idx == 2:
            avg_read_time = total_read_time / read_operations
            print(f"zram的平均一次读: {avg_read_time:.5f} ms")
            avg_write_time = total_write_time / write_operations
            print(f"zram的平均写用时: {avg_write_time:.5f} ms")
        
        
if __name__ == '__main__':
    calculate_avg_time("f2.txt")