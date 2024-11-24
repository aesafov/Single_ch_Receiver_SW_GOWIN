module Top_module
(
    input clkin,
    input reset_n,
    input uart0_rxd,
    output uart0_txd
);

    Gowin_PLLVR_80MGz PLL_80MGz
    (
        .clkout(clkout_80MGz), //output clkout
        .lock(lock), //output lock
        .clkin(clkin) //input clkin
    );

    Gowin_EMPU_Top My_CPU_CM3
    (
        .sys_clk(clkout_80MGz), //input sys_clk
        .gpio(gpio), //inout [15:0] gpio
        .uart0_rxd(uart0_rxd), //input uart0_rxd
        .uart0_txd(uart0_txd), //output uart0_txd
        .reset_n(reset_n) //input reset_n
    );
endmodule