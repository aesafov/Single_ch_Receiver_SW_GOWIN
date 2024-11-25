module Top_module
(
    input clkin,
    input reset_n,
    input uart0_rxd,
    output uart0_txd,
    output led0
);

    wire[15:0] GPIO_io;
    wire [14:0] gpioout_o;

    Gowin_PLLVR_80MGz PLL_80MGz
    (
        .clkout(clkout_80MGz), //output clkout
        .lock(lock), //output lock
        .clkin(clkin) //input clkin
    );

    Gowin_PLLVR_78MGz PLL_78MGz
    (
        .clkout(clkout_78MGz), //output clkout
        .lock(lock_1), //output lock
        .clkin(clkin) //input clkin
    );

    Gowin_EMPU_Top My_CPU_CM3
    (
        //.sys_clk(clkout_80MGz), //input sys_clk My board
        .sys_clk(clkout_78MGz), //input sys_clk Tang Nano4K
        .gpio({gpioout_o,led0}), //inout [15:0] gpio
        .uart0_rxd(uart0_rxd), //input uart0_rxd
        .uart0_txd(uart0_txd), //output uart0_txd
        .reset_n(reset_n) //input reset_n
    );
endmodule