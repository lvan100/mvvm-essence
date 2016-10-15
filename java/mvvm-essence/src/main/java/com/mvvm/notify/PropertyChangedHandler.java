package com.mvvm.notify;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 属性值变化处理器
 */
public class PropertyChangedHandler {

    /**
     * 属性值变化通知列表
     */
    private Map<String, List<IPropertyChangedSupport>> propertyChangedMap = new HashMap<>();

    /**
     * 通知属性值变化事件
     *
     * @param exclude      被排除的通知对象，要求实现 IPropertyChangedSupport 接口。
     * @param source       属性发生变化的对象，要求实现 IPropertyChangedSupport 接口。
     * @param propertyName 发生变化的属性名称
     */
    public void notifyPropertyChanged(IPropertyChangedSupport exclude, IPropertyChangedSupport source, String propertyName) {
        List<IPropertyChangedSupport> notifyList = propertyChangedMap.get(propertyName);
        if (notifyList != null) {
            for (IPropertyChangedSupport notify : notifyList) {
                PRINT_HELPER.enterPrint(this.toString() +
                        ":PropertyChangedHandler.onPropertyChanged.begin");
                {
                    if (notify != exclude) {
                        notify.onPropertyChanged(source, propertyName);
                    } else {

                        PRINT_HELPER.enterPrint(this.toString() +
                                ":PropertyChangedHandler.onPropertyChanged.skip");
                        PRINT_HELPER.exit();
                    }
                }
                PRINT_HELPER.exitPrint(this.toString() +
                        ":PropertyChangedHandler.onPropertyChanged.end");
            }
        }
    }

    /**
     * 添加属性值变化通知接口
     *
     * @param propertyName 发生变化的属性名称
     * @param notify       属性值变化通知接口，要求实现 IPropertyChangedSupport 接口。
     */
    public void addPropertyChangedNotify(String propertyName, IPropertyChangedSupport notify) {
        List<IPropertyChangedSupport> notifyList = propertyChangedMap.get(propertyName);
        if (notifyList == null) {
            notifyList = new ArrayList<>();
            propertyChangedMap.put(propertyName, notifyList);
        }

        notifyList.add(notify);
    }

    /**
     * 移除属性值变化通知接口
     *
     * @param propertyName 发生变化的属性名称
     * @param notify       属性值变化通知接口，要求实现 IPropertyChangedSupport 接口。
     */
    public void removePropertyChangedNotify(String propertyName, IPropertyChangedSupport notify) {
        List<IPropertyChangedSupport> notifyList = propertyChangedMap.get(propertyName);
        if (notifyList != null) {
            notifyList.remove(notify);
        }
    }

}
