package com.mvvm.view;

/**
 * 视图控件接口
 */
public interface View {

    /**
     * 获取视图控件ID
     */
    String getId();

    /**
     * 设置视图控件ID
     */
    void setId(String id);

    /**
     * 刷新控件视图
     */
    void show();

}
