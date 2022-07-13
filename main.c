#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


//����ü ����
struct _info
{
	unsigned long number;
	char id[10], passworld[10], name[20], gender[2], age[2], rank[20], company[30], address[40], post[7], phone[15], handphone[15];

};
typedef struct _info INFO;

struct _pginfo
{
	double ver;
	int record,drecord,number;
	char pgname[40];

};
typedef struct _pginfo PGINFO;

struct _info1
{	
	char id, del;
	int count;
};
typedef struct _info1 INFO1;

//��������
int count = 1;
int dcount = 0;
unsigned int address = sizeof(INFO);
unsigned int address1 = sizeof(INFO1);
int SN = 0;
#define datasize sizeof(INFO)
#define datasize1 sizeof(INFO1)

//���� �Լ���
void insert_member(FILE* fp, FILE* fp1);
void modify_member(FILE* fp);
void delete_member(FILE* fp, FILE* fp1);
void search_member(FILE* fp, FILE* fp1);
void list_member(FILE* fp);
void reset();
void indexing(FILE* fp, FILE* fp1,int num);
void view_help();
void printTitle();


//�ΰ����� �Լ���
void save_data(INFO temp, INFO1 temp1, FILE* fp, FILE* fp1);
void fqsort(INFO temp, FILE* fp);
int disk_comp( FILE* fp);
void disk_swap(FILE* fp, int num1, int num2);
int fbin_search(FILE* fp, char ID[]);
int find_member(FILE* fp,char ID[]);
int get_recount();
void display_member(FILE* fp, int address_1);
int get_offset();
void set_delete(FILE* fp, int num);

int main(void) {

	INFO temp = { 0 };
	INFO temp1 = { 0 };
	FILE* fp = NULL;
	FILE* fp1 = NULL;
	char* file = "member.dat";
	char* file1 = "member.idx";


	fopen_s(&fp, file, "wb+");
	fopen_s(&fp1, file1, "wb+");


	if (fp == NULL) {
		printf("���� ���� ����!!! \n");
		exit(1);
	}

	PGINFO header = { 0.9,count,dcount,NULL,"MMS(Membership Management System)" };

	fwrite(&header, sizeof(PGINFO), 1, fp);
	



	while (1) {


		char select[4];

		printTitle();

		printf("I> ȸ�����\n");
		printf("M> ȸ������ ����\n");
		printf("D> ȸ������ ����\n");
		printf("S> ȸ���˻�\n");
		printf("L> ȸ�����\n");
		printf("N> �ý����ʱ�ȭ\n");
		printf("X> �ڷ�����\n");
		printf("H> ����\n");
		printf("Q> ����\n");

		scanf_s("%s", select, sizeof(select));

		if (strcmp(select, "I") == 0) {
			insert_member(fp,fp1);
		}
		if (strcmp(select, "M") == 0) {
			modify_member(fp);
		}
		if (strcmp(select, "D") == 0) {
			delete_member(fp,fp1);
		}
		if (strcmp(select, "S") == 0) {
			search_member(fp, fp1);
		}
		if (strcmp(select, "L") == 0) {
			list_member(fp);
		}
		if (strcmp(select, "N") == 0) {
			reset();
		}
		if (strcmp(select, "X") == 0) {
			indexing(fp,fp1,SN);
		}
		if (strcmp(select, "H") == 0) {
			view_help();
		}
		if (strcmp(select, "Q") == 0) {
			fclose(fp);
			fclose(fp1);

			exit(1);
		}
	}

	return 0;
}


//���� �Լ�
void insert_member(FILE* fp,FILE* fp1) {
	
	INFO temp;
	char option_1[3];


	printf("\nȸ���� �⺻ ������ �Է��Ͻʽÿ�...\n\n");


	printf("> �� ȣ : "); scanf_s("%d", &temp.number); getchar();
	printf("> ȸ��ID : "); gets_s(temp.id, sizeof(temp.id));
	printf("> ��й�ȣ : "); gets_s(temp.passworld, sizeof(temp.passworld));
	printf("> �� �� : "); gets_s(temp.name, sizeof(temp.name));
	printf("> �� �� : "); gets_s(temp.gender, sizeof(temp.gender));
	printf("> �� �� : "); gets_s(temp.age, sizeof(temp.age));
	printf("> ���� : "); gets_s(temp.rank, sizeof(temp.rank));
	printf("> ȸ��� : "); gets_s(temp.company, sizeof(temp.company));
	printf("> �ּ� : "); gets_s(temp.address, sizeof(temp.address));
	printf("> �����ȣ : "); gets_s(temp.post, sizeof(temp.post));
	printf("> ��ȭ��ȣ : "); gets_s(temp.phone, sizeof(temp.phone));
	printf("> �޴��� : "); gets_s(temp.handphone, sizeof(temp.handphone));

	INFO1 temp1 = { temp.id , NULL, count};
	SN = temp.number;
	while (1)
	{

		printf("S>����, M>����, Q>���� : "); scanf_s("%s", &option_1, sizeof(option_1)); getchar();

		if (strcmp(option_1, "S") == 0) {

			save_data(temp, temp1, fp, fp1);
			fqsort(temp, fp);
			count++;
			address = (unsigned int)(datasize * count);
			address1 = (unsigned int)(datasize1 * count);

		}

		if (strcmp(option_1, "M") == 0) {
			return;
		}

		if (strcmp(option_1, "Q") == 0) {
			fqsort(temp, fp);
			fclose(fp);
			fclose(fp1);
			exit(1);
		}
	}
}

//������ ���� �Լ�
void save_data(INFO temp, INFO1 temp1, FILE* fp, FILE* fp1) {

	fseek(fp1, address1, SEEK_SET);

	fseek(fp, address, SEEK_SET);

	fwrite(&temp, sizeof(INFO), 1, fp);

	fwrite(&temp1, sizeof(INFO1), 1, fp1);


	return;

}

//�Ϸù�ȣ�� ���� ���� ����
void fqsort(INFO temp, FILE* fp) {
	
	disk_comp(fp);
	
	return;

}
	
//������������ ����
int disk_comp(FILE* fp) {
	INFO temp;
	
	int add = datasize;
	
	for (int i = 1; i <= count + 1; i++) {
		fseek(fp, add, SEEK_SET);
		fread(&temp, sizeof(INFO), 1, fp);

		unsigned int num = temp.number;

		
		int add1 = add;
		for (int j = i; j <= count; j++) {
			fseek(fp, add1, SEEK_SET);
			fread(&temp, sizeof(INFO), 1, fp);
			if (temp.number == 0) {
				break;
			}
			if (temp.number < num) {

				disk_swap(fp,add,add1);
			
			}
			add1 += datasize;
		}
		add += datasize;

	}
	return 0;

}


//������ ��ġ �ٲ��ֱ�
void disk_swap(FILE* fp,int num1, int num2) {
	INFO temp;

	fseek(fp, num1, SEEK_SET);
	fread(&temp, sizeof(INFO), 1, fp);

	INFO temp_1 = temp; //���� ��
	

	fseek(fp, num2, SEEK_SET);
	fread(&temp, sizeof(INFO), 1, fp);
	
	

	INFO temp_2 = temp; //ū��
	

	fseek(fp, num2, SEEK_SET);
	fwrite(&temp_1, sizeof(INFO), 1, fp);

	fseek(fp, num1, SEEK_SET);
	fwrite(&temp_2, sizeof(INFO), 1, fp);
	


	return;
}




void modify_member(FILE* fp) {
	char ID[10];
	int num, num1;
	INFO temp;

	printf("������ ����� ID�� �Է��Ͻÿ� : ");
	scanf_s("%s", &ID, sizeof(ID)); getchar();

	num = find_member(fp,ID);

	fseek(fp, datasize * num, SEEK_SET);

	fread(&temp, sizeof(INFO), 1, fp);



	display_member(fp, datasize * num);

	printf("������ �׸��� ���� �ϼ��� : ");
	scanf_s("%d", &num1, sizeof(num1)); getchar();

	printf("�����͸� �Է��ϼ��� : ");


	if (num1 = 1) {
		gets_s(temp.passworld, sizeof(temp.passworld));
	}
	else if (num1 = 2) {
		gets_s(temp.name, sizeof(temp.name));
	}
	else if (num1 = 3) {
		gets_s(temp.gender, sizeof(temp.gender));
	}
	else if (num1 = 4) {
		gets_s(temp.age, sizeof(temp.age));
	}
	else if (num1 = 5) {
		gets_s(temp.rank, sizeof(temp.rank));
	}
	else if (num1 = 6) {
		gets_s(temp.company, sizeof(temp.company));
	}
	else if (num1 = 7) {
		gets_s(temp.address, sizeof(temp.address));
	}
	else if (num1 = 8) {
		gets_s(temp.post, sizeof(temp.post));
	}
	else if (num1 = 9) {
		gets_s(temp.phone, sizeof(temp.phone));
	}
	else if (num1 = 10) {
		gets_s(temp.handphone, sizeof(temp.handphone));
	}

	fseek(fp, datasize * num, SEEK_SET);

	fwrite(&temp, sizeof(INFO), 1, fp);

	return;
}


int find_member(FILE* fp,char ID[]) {
	
	int num;
	
	num = fbin_search(fp, ID);


	return num;
}



int fbin_search(FILE* fp,char ID[]) {
	INFO temp;
	int count = 1;
	int add = datasize;
	int add1 = get_offset();
	for (int i = 1; i < get_recount(); i++) {
		fseek(fp, add, SEEK_SET);

		fread(&temp, sizeof(INFO), 1, fp);

		if (strcmp(ID, temp.id) == 0) {

			break;

		}
		
		count++;
		add += datasize;

	}

	

	return count;

}

int get_recount() {
	return count;
}

void display_member(FILE* fp,int address_1) {

	INFO temp;

	fseek(fp, address_1, SEEK_SET);

	fread(&temp, sizeof(INFO), 1, fp);

	printf("\n > �� ȣ    : %ld\n", temp.number);
	printf(" > ȸ��ID    : %s\n", temp.id);
	printf(" 1. ��й�ȣ    : %s\n", temp.passworld);
	printf(" 2. �̸�    : %s\n", temp.name);
	printf(" 3. ����    : %s\n", temp.gender);
	printf(" 4. ����    : %s\n", temp.age);
	printf(" 5. ����    : %s\n", temp.rank);
	printf(" 6. ȸ���    : %s\n", temp.company);
	printf(" 7. �ּ�    : %s\n", temp.address);
	printf(" 8. �����ȣ    : %s\n", temp.post);
	printf(" 9. ��ȭ��ȣ    : %s\n", temp.phone);
	printf("10. �޴���    : %s\n", temp.handphone);

	return;
}

int get_offset() {
	return address;
}
//�����ϴ� �Լ�
void delete_member(FILE* fp, FILE* fp1) {

	char ID[10],ch[3];
	int num, num1;
	INFO temp;

	printf("������ ����� ID�� �Է��Ͻÿ� : ");
	scanf_s("%s", &ID, sizeof(ID)); getchar();

	num = find_member(fp, ID);

	display_member(fp, datasize * num);

	fseek(fp, datasize * num, SEEK_SET);

	fread(&temp, sizeof(INFO), 1, fp);

	printf("�����Ͻðڽ��ϱ� ?(y/n) : ");
	scanf_s("%s", &ch, sizeof(ch)); getchar();
	
	if (strcmp(ch, "y") == 0) {
		set_delete(fp1,num);
	}
	else
	{
		return;
	}
	return;

}

void set_delete(FILE* fp,int num) {
	INFO1 temp;
	
	fseek(fp, datasize1 * num, SEEK_SET);

	fread(&temp, sizeof(INFO1), 1, fp);
	
	temp.del = "D";
	dcount++;
	return;
	
}

void search_member(FILE* fp, FILE* fp1) {

	char ID[10],ch[3];
	int num;
	INFO temp;

	printf("�˻��� ����� ID�� �Է��Ͻÿ� : ");
	scanf_s("%s", &ID, sizeof(ID)); getchar();

	num = find_member(fp, ID);

	if (count <=  num) {
		printf("����ڸ� ã�� �� �����ϴ�...\n");
		return;
	}
	display_member(fp, datasize * num);

	printf("M>���� Q>���� : ");
	scanf_s("%s", &ch, sizeof(ch)); getchar();

	if (strcmp(ch, "M") == 0) {
		return;
	}
	else if (strcmp(ch, "Q") == 0)
	{
		
		fclose(fp);
		fclose(fp1);
		exit(1);
	}

}

void list_member(FILE* fp) {
	int num = datasize;
	int num1 = get_recount();

	for (int i = 1; i < count; i++) {
		display_member(fp,num);
		printf("�ƹ�Ű�� �����ʽÿ�...");
		getchar(); getchar();
		num += datasize;

	}
	return;
}

void reset() {

	INFO temp = { 0 };
	INFO temp1 = { 0 };
	FILE* fp = NULL;
	FILE* fp1 = NULL;
	char* file = "member.dat";
	char* file1 = "member.idx";


	fopen_s(&fp, file, "wb+");
	fopen_s(&fp1, file1, "wb+");


	if (fp == NULL) {
		printf("���� ���� ����!!! \n");
		exit(1);
	}

	PGINFO header = { 0.9,count,dcount,NULL,"MMS(Membership Management System)" };

	fwrite(&header, sizeof(PGINFO), 1, fp);

	count = 1;
	dcount = 0;

	int address = sizeof(INFO);
	int address1 = sizeof(INFO1);

	return;

}

void indexing(FILE* fp, FILE* fp1,int num) {
	FILE* fp_1 = fp;
	FILE* fp_2 = fp1;
	
	printf("�ڷḦ �����ϰ� �ֽ��ϴ�...\n");
	
	PGINFO header = { 0.9,count,dcount,num,"MMS(Membership Management System)" };
	
	fseek(fp_1,0,SEEK_SET);

	fwrite(&header, sizeof(PGINFO), 1, fp_1);

	printf("Remove old index file member.idx\n");

	printf("Remove old data file member.dat\n");

	printf("Renamed nmember.idx to member.idx\n");

	
	fp1 = fp_2;
	
	printf("Renamed nmember.dat to member.dat\n");

	
	fp = fp_1;

	printf("�ڷ������� �Ϸ�Ǿ����ϴ�...\n");

	getchar(); getchar();

	return;
}

void view_help() {
	printf("----------------------- HELP MESSAGE -----------------------\n");
	printf("���α׷��� ó�� ����Ͻ� ���� ���� ����(member.idx)��\n ������ ����(member.dat)�� �������� �ʽ��ϴ�.\n");
	printf("����, 'N'�� ���� �ý��� �ʱ�ȭ�� ������ ����Ͻʽÿ�.\n");
	printf("��, ������ ������ ������ ��쿡 �� �۾��� �Ͻø� ������ �����͸�\n");
	printf("�Ҿ������ �ǹǷ� �����ؾ� �մϴ�.\n");
	printf("���� �����Ͱ� �������� 'x'�� ���� �ڷḦ �����Ͻʽÿ�.\n");
	printf("�ڷḦ �����Ͻø� ������ �˻��ӵ��� ���˴ϴ�.\n");
	
	getchar(); getchar();

	return;
}

void printTitle(){
	printf("==========================================================\n");
	printf("MMS(Membership Management System) ���� 1�ܰ� ver 0.9\n");
	printf("==========================================================\n\n");
	
	return;
}