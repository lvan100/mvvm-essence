package com.print;

/**
 * 屏幕信息打印助手
 */
public class PrintHelper {

    /**
     * 全局单例
     */
    public static final PrintHelper PRINT_HELPER = new PrintHelper();

    private int deep = -1;

    private PrintHelper() {
    }

    public void enter() {
        deep++;
    }

    public void enterPrint(String str) {
        deep++;
        print(str);
    }

    public void exit() {
        deep--;
    }

    public void exitPrint(String str) {
        print(str);
        deep--;
    }

    public void print(String str) {
        for (int i = 0; i < deep; i++) {
            System.out.print("\t");
        }
        System.out.println(str);
    }

}
