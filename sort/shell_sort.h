#ifndef ALGS4_SORT_SHELL_SORT_H
#define ALGS4_SORT_SHELL_SORT_H

#include "sort_base.h"

// ϣ�������ǲ��������һ�����֣��������˲������������״̬���е��ص�
// ϣ�������˼·�ǣ�һ�����ڼӴ�ļ�����ʹ�ø������ƶ������������ƶ�Ԫ��
// ��һ�����γ� h-th �������к�,���ò��������ڴ���������ļ���ʱ���Ӹ�Ч���ص�
template<typename T>
class ShellSort : public SortBase<T> {
public:
    void Sort(vector<T> &elements) {
        unsigned int size = elements.size();
        unsigned int exchanges = 0;

        // ���Ƚ���һ�����Ե�����ȷ����С��Ԫ��������
        for (unsigned int i = size - 1; i > 0; i--) {
            if (SortBase<T>::Less(elements[i], elements[i - 1])) {
                SortBase<T>::Exch(elements, i, i - 1);
                exchanges++;
            }
        }

        if (exchanges == 0) return;

        // ��������˼·�Ͳ���������Ȼһ�£�ֻ����ʹ����һ���ݼ��� h ��Ϊ�Ƚ�/�ƶ��Ĳ���
        // �� h ���ٵ� 1 ʱ���ͺ���ͨ�Ĳ���������ȫһ���ˣ�����ʱ��������Ѿ���һ������ 4-th ����ļ���
        unsigned int h = 1;
        while (h < size / 3) h = h * 3 + 1;
        while (h >= 1) {
            unsigned int k = h == 1 ? 2 : h;
            for (unsigned int i = k; i < size; i++) {
                T element = elements[i];
                unsigned int j = i;
                while (SortBase<T>::Less(element, elements[j - h])) {
                    elements[j] = elements[j - h];
                    j -= h;
                }
                elements[j] = element;
            }
            h = h / 3;
        }
    }
};

#endif //ALGS4_SORT_SHELL_SORT_H
