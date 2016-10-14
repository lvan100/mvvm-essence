package com.mvvm.notify;

import java.util.ArrayList;
import java.util.List;

/**
 * 值变化通知接口的默认实现
 */
public class NotifyValueChanged<T> implements INotifyValueChanged<T> {

    /**
     * 值变化通知列表
     */
    private List<OnValueChanged> valueChangedList = new ArrayList<>();

    /**
     * 通知值变化
     */
    protected void notifyValueChanged(T newValue) {
        for (OnValueChanged vc : valueChangedList) {
            System.out.println(this.toString() + ":NotifyValueChanged.OnValueChanged");
            vc.onValueChanged(newValue);
        }
    }

    @Override
    public void addValueChanged(OnValueChanged valueChanged) {
        valueChangedList.add(valueChanged);
    }

    @Override
    public void removeValueChanged(OnValueChanged valueChanged) {
        valueChangedList.remove(valueChanged);
    }

}
