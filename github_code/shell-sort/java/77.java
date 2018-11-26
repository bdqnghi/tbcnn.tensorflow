package net.brian.coding.algorithm.crazyjavaimpl;

/**
 * ϣ������
 * �Ӵ�ֱ�Ӳ���������Ԫ��֮��ļ��������Щ�м���Ԫ���н��в������򣬴Ӷ�ʹ����������ƶ�
 * ѡ������h��ΪԪ�ؼ��Ĵ�С�ı�ʾ��������hֵ�ϴ�ʱ��������ÿһ��������Ҫ�ƶ�Ԫ�صĸ�������
 * ���������ƶ��ľ���ܳ������������ͨ�Ĳ����������Ч�ʣ�ÿһ������֮�󶼻��Сh��ֵ
 * ��h��Сʱ��ÿһ��������Ҫ�ƶ�Ԫ�ظ������࣬��ʱ�������Ѿ��ӽ���������������յ�λ��
 * ֱ������������Ϊ1��ϣ������
 * 
 * ����Ϊ1��ϣ���������ֱ�Ӳ�������
 */
//����һ�����ݰ�װ��
class ShellSortDataWrap implements Comparable<ShellSortDataWrap>
{
	int data;
	String flag;
	public ShellSortDataWrap(int data, String flag)
	{
		this.data = data;
		this.flag = flag;
	}
	public String toString()
	{
		return data + flag;
	}
	//����dataʵ����������������ShellSortDataWrap�Ĵ�С
	public int compareTo(ShellSortDataWrap dw)
	{
		return this.data > dw.data ? 1 
			: (this.data == dw.data ? 0 : -1);
	}
}
public class ShellSort
{
	public static void shellSort(ShellSortDataWrap[] data) 
	{
		System.out.println("��ʼ����");
		int arrayLength = data.length;
		//h��������ɱ�����
		int h = 1;
		//��h * 3 + 1�õ��������е����ֵ
		while(h <= arrayLength / 3)
		{
			h = h * 3 + 1;
		}
		while(h > 0)
		{
			System.out.println("===h��ֵ:" + h + "===");
			for (int i = h ; i < arrayLength ; i++ )
			{
				//���������ʱ����֤data[i]��ֵ���ᶪʧ
				ShellSortDataWrap tmp = data[i];
				//i��������ֵ�Ѿ���ǰ������ֵ���󣬱����Ѿ������������
				//��i-1����֮ǰ�������Ѿ�����ģ�i-1������Ԫ�ص�ֵ�������ֵ��
				if (data[i].compareTo(data[i - h]) < 0)
				{
					int j = i - h;
					//�������h��
					for ( ; j >= 0 && data[j].compareTo(tmp) > 0 ; j-=h)
					{
						data[j + h] = data[j];
					}
					//���tmp��ֵ�������λ��
					data[j + h] = tmp;
				}
				System.out.println(java.util.Arrays.toString(data));
			}
			h = (h - 1) / 3;
		}
	}
	public static void main(String[] args)
	{
		ShellSortDataWrap[] data = {
			new ShellSortDataWrap(9 , ""),
			new ShellSortDataWrap(-16 , ""),
			new ShellSortDataWrap(21 , "*"),
			new ShellSortDataWrap(23 , ""),
			new ShellSortDataWrap(-30 , ""),
			new ShellSortDataWrap(-49 , ""),
			new ShellSortDataWrap(21 , ""),
			new ShellSortDataWrap(30 , "*"),
			new ShellSortDataWrap(30 , ""),
		};
		System.out.println("����֮ǰ��\n"
			+ java.util.Arrays.toString(data));
		shellSort(data);
		System.out.println("����֮��\n" 
			+ java.util.Arrays.toString(data));
	}
}
