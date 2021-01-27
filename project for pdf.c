#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<unistd.h>

double covariance(int ds1[], int ds2[], int size)
{
	double sx=0, sy=0, n;
	int x;
	double cov, xbar, ybar, temp=0;
	for(x=0;x<size;x++)
	{
		sx= sx+ ds1[x];
		sy= sy+ ds2[x];
	}
	n= size-1;
	xbar=(double)sx/size;
	ybar=(double)sy/size;
	for(x=0;x<size;x++)
	{
		temp= temp+((ds1[x]-xbar)*(ds2[x]-ybar));
	}
	
	cov=(double)temp/n;
	return(cov);	
}

double detof(double dispmat[4][4],int row, int col)
{
	double detsigma[3][3], determinant;
	int i,j,m=0, n=0;
	
	for(i=0; i<4; i++)
	{
		for(j=0;j<4; j++)
		{
			if(i!=row && j!=col)
			{
				detsigma[m][n]=dispmat[i][j];
				n++;
			}
		}
		if(i!=row)
		m++; n=0;
	}
	
	determinant=(pow(-1,row+col))* (detsigma[0][0]*(((detsigma[1][1])*(detsigma[2][2]))-((detsigma[1][2])*(detsigma[2][1])))-detsigma[0][1]*(((detsigma[1][0])*(detsigma[2][2]))-((detsigma[2][0])*(detsigma[1][2])))+detsigma[0][2]*(((detsigma[1][0])*(detsigma[2][1]))-((detsigma[2][0])*(detsigma[1][1]))));
	
	return(determinant);
}

int main()
{
	printf("Welcome to the Social Media Statistical software\n\n");
	sleep(2);
	printf("\tYou will need to input the number of likes you recieved from various genres of posts,\n\t and the number of followers corresponding to them, \n\tand you will get in result the genre which attracts followers the most.\n\n");
	sleep(4);
	printf("Divide your posts into three classifications or genres and observe the \nnumber of likes you get in an equal number of posts from each genre.\nAlso observe the number of followers you have corresponding to these posts.\n\n");
	sleep(3);
	double dispmat[4][4],sigma11,sigma22,sigma33,sigma44, sigma12, sigma13, sigma14;
	int np, l;
	char g1[30], g2[30], g3[30];
	double parcorr12, parcorr13, parcorr14;
	
	printf("\n");
	printf("\n\tEnter the name of the first genre of your posts \n");
	scanf("%s",g1);
	printf("\n\tEnter the name of the second genre of your posts \n");
	scanf("%s",g2);
	printf("\n\tEnter the name of the third genre of your posts \n");
	scanf("%s",g3);
	printf("\n\tEnter the number of posts in each genre \n");
	scanf("%d",&np);
	
	int dg1[np],dg2[np],dg3[np],df[np];
	
	for(l=0;l<np;l++)
	{
		printf("\n");
		printf("\tEnter the number of likes you got in post %d of genre %s \n",l+1,g1);
		scanf("%d",&dg1[l]);
		printf("\tEnter the number of likes you got in post %d of genre %s \n",l+1,g2);
		scanf("%d",&dg2[l]);
		printf("\tEnter the number of likes you got in post %d of genre %s \n",l+1,g3);
		scanf("%d",&dg3[l]);
		printf("\tEnter the number of followers you had corresponding to these posts\n");
		scanf("%d",&df[l]);
	}
	
	printf("\n\tThe name of your genres are: \n\t%s,\t%s,\t%s\t and final column is the Number of followers\n",g1, g2, g3);
	printf("\t Your data set is:\n");
	for(l=0;l<np;l++)
	{
		printf("\t%d\t%d\t%d\t%d\n",dg1[l], dg2[l], dg3[l], df[l]);
	}
	
	sleep(3);
	
	dispmat[0][0]= covariance(df,df,np);
	dispmat[0][1]= covariance(df,dg1,np);
	dispmat[0][2]= covariance(df,dg2,np);
	dispmat[0][3]= covariance(df,dg3,np);
	dispmat[1][0]= covariance(dg1,df,np);
	dispmat[1][1]= covariance(dg1,dg1,np);
	dispmat[1][2]= covariance(dg1,dg2,np);
	dispmat[1][3]= covariance(dg1,dg3,np);
	dispmat[2][0]= covariance(dg2,df,np);
	dispmat[2][1]= covariance(dg2,dg1,np);
	dispmat[2][2]= covariance(dg2,dg2,np);
	dispmat[2][3]= covariance(dg2,dg3,np);
	dispmat[3][0]= covariance(dg3,df,np);
	dispmat[3][1]= covariance(dg3,dg1,np);
	dispmat[3][2]= covariance(dg3,dg2,np);
	dispmat[3][3]= covariance(dg3,dg3,np);
	
	sigma11= detof(dispmat,0,0);
	sigma22= detof(dispmat,1,1);
	sigma33= detof(dispmat,2,2);
	sigma44= detof(dispmat,3,3);
	sigma12= detof(dispmat,0,1);
	sigma13= detof(dispmat,0,2);
	sigma14= detof(dispmat,0,3);
	
	parcorr12= ((-1)*sigma12)/((sqrt(abs(sigma11)))*(sqrt(abs(sigma22))));
	parcorr13= ((-1)*sigma13)/((sqrt(abs(sigma11)))*(sqrt(abs(sigma33))));
	parcorr14= ((-1)*sigma14)/((sqrt(abs(sigma11)))*(sqrt(abs(sigma44))));
	
	if(parcorr12> parcorr13 && parcorr13> parcorr14)
	printf("\n\tGenre %s brings you most followers, followed by genre %s and then genre %s.\n",g1, g2, g3);
	
	else if(parcorr12> parcorr14 && parcorr14> parcorr13)
	printf("\n\tGenre %s brings you most followers, followed by genre %s and then genre %s.\n",g1, g3, g2);
	
	else if(parcorr13> parcorr12 && parcorr12> parcorr14)
	printf("\n\tGenre %s brings you most followers, followed by genre %s and then genre %s.\n",g2, g1, g3);
	
	else if(parcorr13> parcorr14 && parcorr14> parcorr12)
	printf("\n\tGenre %s brings you most followers, followed by genre %s and then genre %s.\n",g2, g3, g1);
	
	else if(parcorr14> parcorr12 && parcorr12> parcorr13)
	printf("\n\tGenre %s brings you most followers, followed by genre %s and then genre %s.\n",g3, g1, g2);
	
	else if(parcorr14> parcorr13 && parcorr13> parcorr12)
	printf("\n\tGenre %s brings you most followers, followed by genre %s and then genre %s.\n",g3, g2, g1);
	
	else if(parcorr12> parcorr13 && parcorr13== parcorr14)
	printf("\n\tGenre %s brings you most followers, followed by genre %s and then genre %s.\n",g1, g2, g3);
	
	else if(parcorr13> parcorr12 && parcorr12== parcorr14)
	printf("\n\tGenre %s brings you most followers, followed by genre %s and then genre %s.\n",g2, g1, g3);
	
	else if(parcorr14> parcorr12 && parcorr12== parcorr13)
	printf("\n\tGenre %s brings you most followers, followed by genre %s and then genre %s.\n",g3, g1, g2);
	
	else if(parcorr12== parcorr13 && parcorr13== parcorr14)
	printf("\n\tAll genres are equally effective in increasing followers.\n");
	
	return(0);
	getch();
}


