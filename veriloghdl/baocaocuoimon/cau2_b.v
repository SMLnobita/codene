module cau2_b (
    input  wire       CLOCK_50,
    input  wire [1:0] SW,
    input  wire [0:0] KEY,
    output wire [6:0] HEX5, HEX4, HEX3, HEX2, HEX1, HEX0
);
    // --- 1. KHAI BÁO BIẾN ---
    reg [23:0] shift_reg;
    reg [25:0] counter;
    reg [25:0] limit;
    reg        tick;
    reg        running;
    reg [1:0]  key_sync;
    reg        key_prev;
    
    initial begin
        shift_reg = 24'h085FFF;
        counter   = 26'd0;
        tick      = 1'b0;
        running   = 1'b1;
        key_sync  = 2'b11;
        key_prev  = 1'b1;
    end
    
    // --- 2. CHỌN TỐC ĐỘ (SW1) ---
    always @(*) begin
        case (SW[1])
            1'b0: limit = 26'd49_999_999; // 1 Hz
            1'b1: limit = 26'd24_999_999; // 2 Hz
            default: limit = 26'd49_999_999;
        endcase
    end
    
    // --- 3. BỘ CHIA XUNG ---
    always @(posedge CLOCK_50) begin
        if (counter >= limit) begin
            counter <= 26'd0;
            tick    <= 1'b1;
        end else begin
            counter <= counter + 26'd1;
            tick    <= 1'b0;
        end
    end
    
    // --- 4A. ĐỒNG BỘ NÚT NHẤN (2 flip-flop) ---
    always @(posedge CLOCK_50) begin
        key_sync <= {key_sync[0], KEY[0]};
    end
    
    // --- 4B. PHÁT HIỆN SƯỜN XUỐNG ---
    always @(posedge CLOCK_50) begin
        key_prev <= key_sync[1];
        if (key_prev == 1'b1 && key_sync[1] == 1'b0)
            running <= ~running;
    end
    
    // --- 5. LOGIC DỊCH ---
    always @(posedge CLOCK_50) begin
        if (tick && running) begin
            if (SW[0] == 1'b0)
                shift_reg <= {shift_reg[3:0], shift_reg[23:4]};
            else
                shift_reg <= {shift_reg[19:0], shift_reg[23:20]};
        end
    end
    
    // --- 6. GIẢI MÃ HIỂN THỊ ---
    HexDecoder u5 (.in(shift_reg[23:20]), .out(HEX5));
    HexDecoder u4 (.in(shift_reg[19:16]), .out(HEX4));
    HexDecoder u3 (.in(shift_reg[15:12]), .out(HEX3));
    HexDecoder u2 (.in(shift_reg[11:8]),  .out(HEX2));
    HexDecoder u1 (.in(shift_reg[7:4]),   .out(HEX1));
    HexDecoder u0 (.in(shift_reg[3:0]),   .out(HEX0));
endmodule

module HexDecoder(
    input  wire [3:0] in,
    output reg  [6:0] out
);
    always @(*) begin
        case (in)
            4'h0: out = 7'b1000000;
            4'h1: out = 7'b1111001;
            4'h2: out = 7'b0100100;
            4'h3: out = 7'b0110000;
            4'h4: out = 7'b0011001;
            4'h5: out = 7'b0010010;
            4'h6: out = 7'b0000010;
            4'h7: out = 7'b1111000;
            4'h8: out = 7'b0000000;
            4'h9: out = 7'b0010000;
            4'hF: out = 7'b1111111;
            default: out = 7'b1111111;
        endcase
    end
endmodule