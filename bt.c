#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int tu_chi_muc(char tenfile[],char mang_tcm[][24],char mang_dcs[][200],char mang_tkn[][24],int sotkn)
{
  int k=0,flag=0,dt=0,i,n=0,dc=0,cn,sd=1,cs,kt,j;
  char tmp[200],c,intto[4],tmp2[200],*ftmp;
  FILE *f;
  if((f=fopen(tenfile,"r"))==NULL) printf("Khong mo duoc file %s\n",tenfile);
  else 
    {
      while(feof(f)==0) 
       {
	 c =  fgetc(f);
	 if(c == '.') dc=1;
	 if((c==' ')||(c=='\t'))
	   if (dc==0) flag=1;
	 if((c=='\n')||(c=='\r')) sd++;	
	 if(c<=90&&c>=65)
	  {
	    if(flag==1) {dt=1;flag=0;}
	    else {tmp[k++]=c+32;dt=0;}
	  }
	else if(c<=122&&c>=97)
	  {
	    if(dt==1) k=0;
	    else tmp[k++]=c;
	    flag=0;
	  }
	else
	  {
	    if((c!=' ')&&(c!='\t'))
	      { dc =0;flag=0;}
	    dt=0;
	    if(k!=0) 
	      {
		cn=0;
		tmp[k]='\0';
		for(i=0;i<sotkn;i++)
		  if(strcmp(mang_tkn[i],tmp)==0) cn++;
		if(cn==0) 
		  {
		    for(i=0;i<n;i++)
		      if(strcmp(mang_tcm[i],tmp)==0) break;
		    if(i==n)
		      {
			strcpy(mang_tcm[i],tmp);
			sprintf(tmp,"%d,%d",1,sd);
			strcpy(mang_dcs[i],tmp);
			n++;
		      }
		    else 
		      {
			kt=0;
			j=0;
			tmp[0]='\0';
			//printf("%s\n",mang_tcm[i]);
		     	ftmp=strtok(mang_dcs[i],",");
			while(ftmp!=NULL)
			  {
			    cs=atoi(ftmp);
			    if(kt==0)
			      {
				cs++;kt++;sprintf(tmp2,"%d",cs);
			      }
			    else 
			      sprintf(tmp2,",%d",cs);
			    if(cs==sd) j++;
			    strcat(tmp,tmp2);
			    ftmp=strtok(NULL,",");
			  }
			if(j==0) sprintf(tmp2,",%d",sd);
			strcat(tmp,tmp2);
			strcpy(mang_dcs[i],tmp);
		      }
		  }
		k=0;
	      }
	  }
       }
      return n;
    }
  return 0;
}
int tu_khong_nghia(char tenfile[],char mang_tkn[][24])
{
  int k=0;
  char tmp[200];
  FILE *f;
  if((f=fopen(tenfile,"r"))==NULL) printf("Khong mo duoc file %s\n",tenfile);
  else 
    {
      while(feof(f)==0) 
       {
	 fscanf(f,"%s\n",tmp);
	 strcpy(mang_tkn[k],tmp);
	 k++;
       }
      return k;
    }
  return 0;
}
int int_compare(void const* x,void const* y)
{
  return strcmp((char*)x,(char*)y);
}
int main()
{
  int sotkn,j,sotcm,i;
  char mang_tkn[200][24];
  char mang_tcm[200][24];
  char mang_tmp[200][24];
  char mang_dcs[200][200];
  sotkn = tu_khong_nghia("stopw.txt",mang_tkn);
  sotcm = tu_chi_muc("vanban.txt",mang_tcm,mang_dcs,mang_tkn,sotkn);
  for(i=0;i<sotcm;i++)
    strcpy(mang_tmp[i],mang_tcm[i]);
   qsort(mang_tmp,sotcm,24*sizeof(char),int_compare);
  for(i=0;i<sotcm;i++)
    {
      printf("%s ",mang_tmp[i]);
       for(j=0;j<sotcm;j++)
	 if(strcmp(mang_tcm[j],mang_tmp[i])==0) break;
       printf("%s \n",mang_dcs[j]);
    }
}
