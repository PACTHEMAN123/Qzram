def convert_to_bytes(size_str):
    """将不同单位（B, K, M, G）转换为字节数"""
    unit_multipliers = {'B': 1, 'K': 1024, 'M': 1024**2, 'G': 1024**3}
    try:
        size = size_str[:-1]
        unit = size_str[-1]
        return int(float(size) * unit_multipliers[unit])
    except ValueError:
        return -1  # 返回-1表示无法转换

def calculate_compression_rate(file_path):
    with open(file_path, 'r') as file:
        # 读取并按空行分割内容
        sections = file.read().split('\n\n')

    for idx, section in enumerate(sections, start=1):
        total_compression_rate = 0
        count = 0

        for line in section.splitlines():
            # 按空格分割每行，获取压缩前和压缩后的大小
            parts = line.split()
            if len(parts) < 4:
                continue  # 忽略不完整的行

            original_size = parts[2]  # 压缩前大小
            compressed_size = parts[3]  # 压缩后大小

            # 转换大小为字节
            original_size_bytes = convert_to_bytes(original_size)
            compressed_size_bytes = convert_to_bytes(compressed_size)

            # 如果转换失败（返回-1），跳过该行
            if original_size_bytes == -1 or compressed_size_bytes == -1:
                continue

            # 计算压缩率
            if original_size_bytes > 0:
                compression_rate = compressed_size_bytes / original_size_bytes
                total_compression_rate += compression_rate
                count += 1

        if idx == 1:
            avg_compression_rate = 1 - total_compression_rate / count
            print(f"qzram的平均压缩率: {avg_compression_rate:.5f}")

        if idx == 2:
            avg_compression_rate = 1 - total_compression_rate / count
            print(f"zram的平均压缩率: {avg_compression_rate:.5f}")


if __name__ == '__main__':
    calculate_compression_rate("f1.txt")