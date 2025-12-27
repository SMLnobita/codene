module Lab6_Bai3 (
    input  wire       CLOCK_50,
    input  wire [1:0] SW,        // SW[0]: Tốc độ, SW[1]: Hướng đếm
    input  wire [0:0] KEY,       // Nút nhấn Reset (KEY[0])
    output reg  [6:0] HEX0       // LED hiển thị giá trị đếm
);

    // --- KHAI BÁO BIẾN ---
    reg [25:0] count_div;        // Biến đếm chia xung
    reg [25:0] limit;            // Giới hạn đếm (tùy tốc độ)
    wire chophep;                // Tín hiệu kích hoạt đếm (tick)
    
    reg [3:0] counter_4bit;      // Biến đếm giá trị chính (0-15)

    // Khởi tạo giá trị ban đầu để tránh lỗi mô phỏng
    initial begin
        count_div    = 0;
        counter_4bit = 0;
    end

    // --- PHẦN 1: BỘ CHIA XUNG (Clock Divider) ---
    // Chọn tốc độ dựa vào SW[0]
    always @(*) begin
        if (SW[0] == 1'b0)
            limit = 50000000 - 1;            // 1 Hz (Chậm)
        else
            limit = 12500000 - 1;            // 4 Hz (Nhanh)
    end

    // Tạo xung "cho phép" (chophep) theo đúng thời gian thực
    always @(posedge CLOCK_50) begin
        if (count_div >= limit)
            count_div <= 0;
        else
            count_div <= count_div + 1'b1;
    end
    
    assign chophep = (count_div == limit);

    // --- PHẦN 2: BỘ ĐẾM 4-BIT (Up/Down Counter) ---
    // Thiết kế có Reset Đồng bộ (Synchronous Reset)
    // SW[1] = 1: Đếm lên (Up), SW[1] = 0: Đếm xuống (Down)
    // KEY[0]: Reset (Active Low - Nhấn là mức 0)
    
    always @(posedge CLOCK_50) begin
        // 1. Kiểm tra Reset trước (Ưu tiên cao nhất)
        if (KEY[0] == 1'b0) begin
            counter_4bit <= 4'b0000;           // Reset về 0
        end
        // 2. Nếu không Reset thì kiểm tra tín hiệu cho phép đếm
        else if (chophep) begin
            if (SW[1] == 1'b1)
                counter_4bit <= counter_4bit + 1'b1;  // Đếm lên
            else
                counter_4bit <= counter_4bit - 1'b1;  // Đếm xuống
        end
    end

    // --- PHẦN 3: GIẢI MÃ LED 7 ĐOẠN (Decoder) ---
    // Hiển thị giá trị counter_4bit ra HEX0 (0-9, A-F)
    // Active Low (0 là Sáng)
    always @(*) begin
        case (counter_4bit)
            4'h0: HEX0 = 7'b1000000;           // Số 0
            4'h1: HEX0 = 7'b1111001;           // Số 1
            4'h2: HEX0 = 7'b0100100;           // Số 2
            4'h3: HEX0 = 7'b0110000;           // Số 3
            4'h4: HEX0 = 7'b0011001;           // Số 4
            4'h5: HEX0 = 7'b0010010;           // Số 5
            4'h6: HEX0 = 7'b0000010;           // Số 6
            4'h7: HEX0 = 7'b1111000;           // Số 7
            4'h8: HEX0 = 7'b0000000;           // Số 8
            4'h9: HEX0 = 7'b0010000;           // Số 9
            4'hA: HEX0 = 7'b0001000;           // Chữ A
            4'hB: HEX0 = 7'b0000011;           // Chữ b
            4'hC: HEX0 = 7'b1000110;           // Chữ C
            4'hD: HEX0 = 7'b0100001;           // Chữ d
            4'hE: HEX0 = 7'b0000110;           // Chữ E
            4'hF: HEX0 = 7'b0001110;           // Chữ F
            default: HEX0 = 7'b1111111;        // Tắt hết (Trường hợp lỗi)
        endcase
    end

endmodule