# mvvm-essence

当前数据绑定的实现有两个版本：一个版本是类WPF模式，另一种是纯Model模式。WPF将绑定源称为Model，而将绑定目标称为DependencyObject，这可能一定程度上掩盖了数据绑定背后实现的机制，实际上WPF中的Model和DependencyObject应该是同源的，所以基于此论断发展出了纯Model模式。在纯Model模式中，所有的Model都是可绑定的，这样就将WPF中的Model和DependencyObject合并成为一个概念——BindableModel，可绑定的Model。

对比一下即可发现，两种实现各有优劣：1）类WPF模式对模型的定义规定了太多规则，需要实现PropertyChangedHandler对象，需要实现IPropertyChangedSupport接口，这个过程中用户需要些太多的代码，而纯Model模式则简单的多，用户仅仅只需要实现一个用Model封装好的对象；2）纯Model模式的优点1又成为它的一项缺点，类WPF模式使用未封装过的类型定义值，所以它的Getter和Setter函数的实现没有任何变化，而纯Model模式使用的是封装过的类型，所以除了针对原始值的Getter和Setter函数之外，还应该暴露一个Model的Getter函数；3）类WPF模式的优点2又恰恰成为它的缺点之一，用户必须在Setter函数中自行实现值的比较和决定是否发出事件通知这两个动作，而在纯Model模式下则无需如此，用户只需要对值实现equals函数即可，对Model赋值的时候会自动完成这两个步骤。

在允许使用反射机制的条件下，类WPF模式的状况会有所改观，但也仅仅是简化了对IPropertyChangedSupport接口的实现（可以通过反射实现getProperty和setProperty），对模型的其他约束仍然是必须的。

总的来说，使用类WPF模式对模型的定义会更加灵活，但是也要写更多代码；而使用纯Model模式则在赋值和取值时多调用一个函数。这两个实现都是优点恰恰是缺点。

## 纯Model模式

### Model

```
public class Student {

    // 学生姓名模型
    public final Model<String> nameValue = new Model<>("");

    //学生分数模型
    public final Model<Integer> scoreValue = new Model<>(0);

}
```

### View

```
public class TextBox extends AbstractView {

    /**
     * 输入框文本数据模型
     */
    public final Model<String> textValue = new Model<>("");

}
```


### ViewModel

```
public class StudentViewModel {

    // 学生信息
    public Student student = new Student();

    // 学生信息视图
    public StudentView studentView = new StudentView("studentView");

    public StudentViewModel() {

        DataBinding<String> binding = new DataBinding<>(BindingType.TwoWay, student.scoreValue);

        binding.setValueConverter(new ValueConverter<String>() {

            @Override
            public String convert(Object value) {
                return value.toString();
            }

            @Override
            public Object reverseConvert(String value) {
                return Integer.valueOf(value);
            }

        });

        studentView.textBoxStudentScore.textValue.setDataBinding(binding);

        student.setScore(45);
        studentView.textBoxStudentScore.setText("75");
    }

}
```

## WPF模式

### Model

Model需要实现IPropertyChangedSupport接口并在值更新时通知变化。

```
public class Student implements IPropertyChangedSupport {

    private String name;
    public static final String nameProperty = "name";

    public String getName() {
        return name;
    }

    public void setName(String name) {
		if (!Objects.deepEquals(this.name, name)) {
			this.name = name;
			handler.notifyPropertyChanged(this, nameProperty);
		}
    }

    /**
     * 属性变化处理器
     */
    private PropertyChangedHandler handler = new PropertyChangedHandler();

    @Override
    public PropertyChangedHandler getPropertyChangedHandler() {
        return handler;
    }

}
```

### View 

View需要创建DependencyObject并为其提供绑定。

```
public class TextBox extends AbstractView {

    public static final String textProperty = "textValue";
    private DependencyObject<String> textValue = new DependencyObject<>("");

    public DependencyObject<String> getText() {
        return textValue;
    }

    public void setText(String value) {
        textValue.setValue(value);
    }

    /**
     * 为属性设置数据绑定。
     */
    public void setDataBinding(String propertyName, DataBinding<?> binding) {
        if (textProperty.equals(propertyName)) {
            textValue.setDataBinding((DataBinding<String>) binding);
        }
    }

}
```

### ViewModel

ViewModel需要连接数据模型和View的DependencyObject对象。

```
public class StudentViewModel {

    // 学生信息
    public Student student = new Student();

    // 学生信息视图
    public StudentView studentView = new StudentView("studentView");

    public StudentViewModel() {

        DataBinding<String> binding = new DataBinding<>(
                BindingType.TwoWay, student, Student.scoreProperty);

        binding.setValueConverter(new ValueConverter<String>() {

            @Override
            public String convert(Object value) {
                return value.toString();
            }

            @Override
            public Object reverseConvert(String value) {
                return Integer.valueOf(value);
            }

        });

        studentView.textBoxStudentScore.setDataBinding(
                TextBox.textProperty, binding);
		
        student.setScore(45);
        studentView.textBoxStudentScore.setText("75");
    }

}
```
