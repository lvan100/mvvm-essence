package com.mvvm.model;

import java.util.Collection;
import java.util.Iterator;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 集合数据模型
 */
public class CollectionModel<T> extends Model<Collection<T>> implements Collection<T> {

    public CollectionModel(Collection<T> value) {
        super(value);
    }

    public CollectionModel(boolean readOnly, Collection<T> value) {
        super(readOnly, value);
    }

    @Override
    public int size() {
        return getValue().size();
    }

    @Override
    public boolean isEmpty() {
        return getValue().isEmpty();
    }

    @Override
    public boolean contains(Object o) {
        return getValue().contains(o);
    }

    @Override
    public Iterator<T> iterator() {
        return getValue().iterator();
    }

    @Override
    public Object[] toArray() {
        return getValue().toArray();
    }

    @Override
    public <T1> T1[] toArray(T1[] a) {
        return getValue().toArray(a);
    }

    @Override
    public boolean add(T t) {

        PRINT_HELPER.enterPrint(this.toString() + ":add.begin");
        boolean result = getValue().add(t);
        PRINT_HELPER.exitPrint(this.toString() + ":add.end");

        notifyValueChanged();

        return result;
    }

    @Override
    public boolean remove(Object o) {

        PRINT_HELPER.enterPrint(this.toString() + ":remove.begin");
        boolean result = getValue().remove(o);
        PRINT_HELPER.exitPrint(this.toString() + ":remove.end");

        notifyValueChanged();

        return result;
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        return getValue().containsAll(c);
    }

    @Override
    public boolean addAll(Collection<? extends T> c) {

        PRINT_HELPER.enterPrint(this.toString() + ":addAll.begin");
        boolean result = getValue().addAll(c);
        PRINT_HELPER.exitPrint(this.toString() + ":addAll.end");

        notifyValueChanged();

        return result;
    }

    @Override
    public boolean removeAll(Collection<?> c) {

        PRINT_HELPER.enterPrint(this.toString() + ":removeAll.begin");
        boolean result = getValue().removeAll(c);
        PRINT_HELPER.exitPrint(this.toString() + ":removeAll.end");

        notifyValueChanged();

        return result;
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        return getValue().retainAll(c);
    }

    @Override
    public void clear() {
        PRINT_HELPER.enterPrint(this.toString() + ":clear.begin");
        {
            getValue().clear();
        }
        PRINT_HELPER.exitPrint(this.toString() + ":clear.end");

        notifyValueChanged();
    }

}
