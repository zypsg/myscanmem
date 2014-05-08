#include <string.h>
#include <jni.h>
#include <stdio.h>

jstring combine_jstring(JNIEnv* env, jstring str1, jstring str2)
{
	jboolean b_ret;
	const char *s1 = (*env)->GetStringUTFChars(env, str1, &b_ret);
	const char *s2 = (*env)->GetStringUTFChars(env, str2, &b_ret);
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	char *new_str = (char *)malloc(n1+n2+1);
	memset(new_str, 0, n1+n2+1);
	strcat(new_str, s1);
	strcat(new_str, s2);
	jstring ret_str = (*env)->NewStringUTF(env,(const char *)new_str);
	free(new_str);

	return ret_str;
}


jstring JNICALL Java_com_example_jnidemo_MainActivity_getStringFromJNI(
		JNIEnv* env, jobject thiz) {
	return (*env)->NewStringUTF(env,
			"JniDemo, Hello from Java_com_example_jnidemo_MainActivity_getStringFromJNI!");
}

JNIEXPORT jint JNICALL Java_com_example_jnidemo_MainActivity_jniStaticShowMessage(
		JNIEnv *env, jobject thiz, jobject thizb, jstring thizc, jstring thizd) {
	jclass cls = (*env)->FindClass(env,"com/example/jnidemo/MainActivity");
	if(cls != NULL){

		jmethodID id = (*env)->GetStaticMethodID(env,cls,"staticShowMessage","(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)I");

		if(id != NULL){
			return (*env)->CallStaticIntMethod(env,cls,id,thizb,thizc,thizd);
		}
	}
	return 1;
}

JNIEXPORT  jint JNICALL Java_com_example_jnidemo_MainActivity_jniShowMessage(JNIEnv *env, jobject thiz,jobject thizb, jstring thizc, jstring thizd){
	jclass cls = (*env)->FindClass(env,"com/example/jnidemo/MainActivity");
	if(cls != NULL){
		jstring str ;
		jmethodID strText_id = (*env)->GetMethodID(env,cls,"getTestString","()Ljava/lang/String;");
		if(strText_id != NULL){
			str = (*env)->CallObjectMethod(env, thiz, strText_id);
		}

		jmethodID showMessage_id = (*env)->GetMethodID(env, cls, "showMessage","(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)I");
		if(showMessage_id != NULL){
			return (*env)->CallIntMethod(env, thiz, showMessage_id, thizb,  thizc, combine_jstring(env, thizc, str));
		}
	}
}



