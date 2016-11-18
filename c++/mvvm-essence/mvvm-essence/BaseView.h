#pragma once

#include <vector>
using namespace std;

namespace Framework {

	class BaseView;

	/* 布局 */
	class Layout {

	private:
		BaseView* _owner;
		vector<BaseView*> views;

	public:
		Layout(BaseView* owner)
			: _owner(owner) {
		}

		void addView(BaseView* view) {
			views.push_back(view);
		}

		virtual void reposition() {

		}

	};

	/* 视图 */
	class BaseView {

	private:
		/* 布局 */
		Layout* _layout;

		/* 父视图 */
		BaseView* _parent;

		/* 子视图 */
		vector<BaseView*> _child;

	public:
		BaseView(BaseView* parent)
			: _parent(parent)
			, _layout(new Layout(this)) {
		}

		void addView(BaseView* view) {
			_layout->addView(view);
			_child.push_back(view);
		}
	};

}