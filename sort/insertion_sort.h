#ifndef ALGS4_SORT_INSERTION_SORT_H
#define ALGS4_SORT_INSERTION_SORT_H

#include "sort_base.h"

// ��������Ҳ��һ�� O(N^2) ʱ��������㷨������Ч�ʺ�����Ԫ�ص�����״̬�йء�
// ��������ƽ�� (N^2) / 4 �αȽϺͽ�������� (N^2) / 2 �αȽϺͽ�������� (N-1) �αȽϺ� 0 �ν���
// ����ͨ���ѽϴ�Ԫ�������ƶ��������ǽ���Ԫ����������Ч�ʡ�
template<typename T>
class InsertionSort : public SortBase<T> {
public:
    static void Sort(vector<T> &elements) {
        unsigned int size = elements.size();
        unsigned exchanges = 0;
        // ���Ƚ���һ�����Ե�����ȷ����С��Ԫ��������
        for (unsigned int i = size - 1; i > 0; i--) {
            if (SortBase<T>::Less(elements[i], elements[i - 1])) {
                SortBase<T>::Exch(elements, i, i - 1);
                exchanges++;
            }
        }
        if (exchanges == 0) return;

        // ��С��������ǰ����һ��������ģ�����ֱ�Ӵӵ�������ʼ
        for (unsigned int i = 2; i < size; i++) {
            // ѡ����ǰ���в����Ԫ��
            T element = elements[i];

            // j �Ǵ�������λ��
            unsigned int j = i;

            // ֻҪѡ����Ԫ�ر� j ��ߵ�Ԫ��С...
            while (SortBase<T>::Less(element, elements[j - 1])) {  // ��С���Ѿ����������� while ѭ��һ������ j = 1 ʱ����
                // �Ͱ�С��Ԫ������һλ...
                elements[j] = elements[j - 1];
                // �ٰ� j �����ƶ�һλ;
                j--;
            }
            // �����ѡ����Ԫ�ز��뵽 j ��λ��
            elements[j] = element;
        }
    }
};

#endif //ALGS4_SORT_INSERTION_SORT_H
