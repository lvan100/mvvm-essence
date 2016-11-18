#pragma once

#include <vector>
using namespace std;

namespace Framework {

	class BaseView;

	/* ���� */
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

	/* ��ͼ */
	class BaseView {

	private:
		/* ���� */
		Layout* _layout;

		/* ����ͼ */
		BaseView* _parent;

		/* ����ͼ */
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