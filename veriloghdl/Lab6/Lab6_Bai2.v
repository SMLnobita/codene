module Lab6_Bai2 (
    input  wire        CLOCK_50,
    input  wire [1:0]  SW,
    output reg  [6:0]  HEX5, HEX4, HEX3, HEX2, HEX1, HEX0
);

    reg [25:0] counter;
    reg [25:0] limit;
    
    wire chophep;

    reg [2:0] status;
    
    initial begin
        counter = 0;
        status  = 0;
    end
    
    always @(*) begin
        case (SW)
            2'b00:   limit = 50000000 - 1;
            2'b01:   limit = 25000000 - 1;
            2'b10:   limit = 12500000 - 1;
            2'b11:   limit = 6250000  - 1;
            default: limit = 50000000 - 1;
        endcase
    end

    always @(posedge CLOCK_50) begin
        if (counter >= limit)
            counter <= 0;
        else
            counter <= counter + 1'b1;
    end
    
    assign chophep = (counter == limit);

    always @(posedge CLOCK_50) begin
        if (chophep) begin
            if (status == 3'd5)
                status <= 3'd0;
            else
                status <= status + 1'b1;
        end
    end

    always @(*) begin
        HEX5 = 7'b1111111;
        HEX4 = 7'b1111111;
        HEX3 = 7'b1111111;
        HEX2 = 7'b1111111;
        HEX1 = 7'b1111111;
        HEX0 = 7'b1111111;

        case (status)
            3'd0: begin
                HEX5 = 7'b0001001;
                HEX4 = 7'b1001111;
            end
            3'd1: begin
                HEX4 = 7'b0001001;
                HEX3 = 7'b1001111;
            end
            3'd2: begin
                HEX3 = 7'b0001001;
                HEX2 = 7'b1001111;
            end
            3'd3: begin
                HEX2 = 7'b0001001;
                HEX1 = 7'b1001111;
            end
            3'd4: begin
                HEX1 = 7'b0001001;
                HEX0 = 7'b1001111;
            end
            3'd5: begin
                HEX0 = 7'b0001001;
                HEX5 = 7'b1001111;
            end
            default: begin
            end
        endcase
    end

endmodule