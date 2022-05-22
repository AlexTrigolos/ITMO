import { Injectable } from '@nestjs/common';
import { PrismaClient } from '@prisma/client';
import { DeleteUserDto } from './dto/delete-user.dto';
import { CreateUserDto } from './dto/create-user.dto';
import { AddPostUserDto } from './dto/addPost-user.dto';
import { SetUserNameDto } from './dto/setName-user.dto';

const prisma = new PrismaClient();

@Injectable()
export class UsersService {
  async create(user: CreateUserDto) {
    let IdNewUser;
    const a = await prisma.user.findMany({ select: { id: true } });
    const lst: number[] = [];
    for (let i = 0; i <= a.length; i++) {
      lst.push(i);
    }
    for (let i = 0; i < a.length; i++) {
      delete lst[a[i].id];
    }
    for (let i = 0; i <= a.length; i++) {
      if (lst[i] != undefined) {
        IdNewUser = lst[i];
        break;
      }
    }
    return await prisma.user.create({
      data: {
        id: IdNewUser,
        email: user.email,
        name: user.name,
        posts: {},
      },
      select: {
        id: true,
        email: true,
        name: true,
        posts: true,
      },
    });
  }

  async findAll(page = 1) {
    return await prisma.user.findMany({
      skip: 5 * (page - 1),
      take: 5,
      select: {
        id: true,
        email: true,
        name: true,
        posts: true,
      },
    });
  }

  async delete(deleteUserDto: DeleteUserDto) {
    const delPosts = await prisma.post.findMany({
      select: {
        id: true,
        authorId: true,
      },
    });
    const delUser = await prisma.user.findMany({
      where: {
        email: deleteUserDto.email,
      },
      select: {
        id: true,
      },
    });
    const rtn = await prisma.user.delete({
      where: {
        email: deleteUserDto.email,
      },
      select: {
        id: true,
        email: true,
        name: true,
        posts: true,
      },
    });
    for (let i = 0; i < delPosts.length; i++) {
      if (delPosts[i].authorId == delUser[0].id) {
        await prisma.post.delete({
          where: {
            id: delPosts[i].id,
          },
        });
      }
    }
    return rtn;
  }

  async addPostForUser(addPostUserDto: AddPostUserDto) {
    return await prisma.user.update({
      where: {
        email: addPostUserDto.email,
      },
      data: {
        posts: {
          connect: {
            id: addPostUserDto.postId,
          },
        },
      },
      select: {
        id: true,
        email: true,
        name: true,
        posts: true,
      },
    });
  }

  async setUserName(setUserNameDto: SetUserNameDto) {
    return await prisma.user.update({
      where: {
        email: setUserNameDto.email,
      },
      data: {
        name: setUserNameDto.name,
      },
      select: {
        id: true,
        email: true,
        name: true,
        posts: true,
      },
    });
  }
}
