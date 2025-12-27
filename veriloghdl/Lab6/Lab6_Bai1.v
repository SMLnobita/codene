module Lab6_Bai1 (
    input wire CLOCK_50,
    input wire [1:0] SW,
    output reg LEDR // Phải là reg vì được gán giá trị trong always
);

    // Khai báo biến đếm và biến giới hạn
    reg [25:0] counter;
    reg [25:0] limit;

    // 1. Mạch tổ hợp: Xác định giới hạn đếm dựa vào Switch
    // Dùng blocking (=) cho mạch tổ hợp [cite: 125]
    always @(*) begin
        case (SW)
            2'b00: limit = 25000000 - 1; // 1 Hz (Trừ 1 vì đếm từ 0)
            2'b01: limit = 12500000 - 1; // 2 Hz
            2'b10: limit = 6250000 - 1;  // 4 Hz
            2'b11: limit = 3125000 - 1;  // 8 Hz
        endcase
    end

    // 2. Mạch tuần tự: Đếm và so sánh
    // Dùng non-blocking (<=) cho mạch tuần tự 
    always @(posedge CLOCK_50) begin
        if (counter >= limit) begin
            counter <= 0;       // Reset bộ đếm khi đạt giới hạn
            LEDR <= ~LEDR;      // Đảo trạng thái LED
        end else begin
            counter <= counter + 1'b1; // Tăng đếm
        end
    end

endmodule